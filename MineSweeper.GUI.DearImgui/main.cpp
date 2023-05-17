#include "imgui/imgui.h"
#include <glad/glad.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "GameManager.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}



#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	/* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

	(void)pInput;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(580, 660, "Chess", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (gladLoadGL() == 0)
	{
		return -1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	io.Fonts->AddFontFromFileTTF("./Font/TaipeiSansTCBeta-Bold.ttf", 14, NULL, io.Fonts->GetGlyphRangesChineseFull());

	//credit: https://github.com/mackron/miniaudio
	//BGM player
	ma_device device;
	{
		ma_result result;
		ma_decoder decoder;
		ma_device_config deviceConfig;

		/*if (argc < 2) {
			printf("No input file.\n");
			return -1;
		}*/

		result = ma_decoder_init_file("./Audio/Dmitri Shostakovich - Waltz No. 2.mp3", NULL, &decoder);
		if (result != MA_SUCCESS) {
			return -2;
		}

		/*
		A decoder is a data source which means we just use ma_data_source_set_looping() to set the
		looping state. We will read data using ma_data_source_read_pcm_frames() in the data callback.
		*/
		ma_data_source_set_looping(&decoder, MA_TRUE);

		deviceConfig = ma_device_config_init(ma_device_type_playback);
		deviceConfig.playback.format = decoder.outputFormat;
		deviceConfig.playback.channels = decoder.outputChannels;
		deviceConfig.sampleRate = decoder.outputSampleRate;
		deviceConfig.dataCallback = data_callback;
		deviceConfig.pUserData = &decoder;

		if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
			printf("Failed to open playback device.\n");
			ma_decoder_uninit(&decoder);
			return -3;
		}

		if (ma_device_start(&device) != MA_SUCCESS) {
			printf("Failed to start playback device.\n");
			ma_device_uninit(&device);
			ma_decoder_uninit(&decoder);
			return -4;
		}
		device.masterVolumeFactor = 0.3f;
		//printf("Press Enter to quit...");
		//getchar();

		/*ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);*/

		//return 0;
	}

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_Minesweeper_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	string FileName[6]{ "_pawn_png_128px.png","_knight_png_128px.png" ,
		"_bishop_png_128px.png" ,"_rook_png_128px.png" ,
		"_queen_png_128px.png" ,"_king_png_128px.png" };

	bool gameStart = false;

	int my_image_width = 0;
	int my_image_height = 0;
	GLuint black_texture = 0, white_texture = 0, empty_texture = 0, bg_texture, test_texture;
	GLuint w_texture[6]{ 0 };
	GLuint b_texture[6]{ 0 };
	for (int i = 0; i < 6; i++)
	{
		string tmp = "./Image/w" + FileName[i];
		LoadTextureFromFile(tmp.c_str(), &w_texture[i], &my_image_width, &my_image_height);
		tmp = "./Image/b" + FileName[i];
		LoadTextureFromFile(tmp.c_str(), &b_texture[i], &my_image_width, &my_image_height);
	}
	LoadTextureFromFile("./Image/black.png", &black_texture, &my_image_width, &my_image_height);
	LoadTextureFromFile("./Image/white.png", &white_texture, &my_image_width, &my_image_height);
	LoadTextureFromFile("./Image/empty.png", &empty_texture, &my_image_width, &my_image_height);
	LoadTextureFromFile("./Image/bg.png", &bg_texture, &my_image_width, &my_image_height);

	GameManager Game;
	//Reversi Game;

	float button_size = 45;
	float dummy_size = 54.8;
	float space = 5.1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Poll for and process events */
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// 4. MineSweeper board
		if (show_Minesweeper_window)
		{
			ImGui::Begin("MineSweeper Board");
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					std::string buttonName = std::to_string(i) + "," + std::to_string(j);
					if (ImGui::Button(buttonName.c_str()))
					{
						std::cout << "LeftClick at row:" << i << " col:" << j << std::endl;
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
					{
						std::cout << "RightClick at row:" << i << " col:" << j << std::endl;
					}

					ImGui::SameLine();
				}
				ImGui::NewLine();
			}
			ImGui::End();
		}

		//window
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0), 0, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
			ImGui::SetNextWindowBgAlpha(0);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
			ImGui::Begin("background", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoBringToFrontOnFocus |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoScrollbar);
			ImGui::Image((void*)(intptr_t)bg_texture, ImGui::GetContentRegionAvail());
			ImGui::End();
			ImGui::PopStyleVar(2);
		}



		{
			ImGui::SetNextWindowPos(ImVec2(60, 18), 0, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
			ImGui::SetNextWindowBgAlpha(0);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
			ImGui::Begin("Chess Game", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove | //ImGuiWindowFlags_NoBringToFrontOnFocus |
				ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
			if (gameStart) {
				GLuint turn_tex;
				if (Game.getTurn() == Color::Black)
					turn_tex = black_texture;
				else
					turn_tex = white_texture;
				ImGui::SetCursorPos(ImVec2(307, 20));
				ImGui::Text(u8"目前回合");
				ImGui::SetCursorPos(ImVec2(300, 40));
				ImGui::Image((void*)(intptr_t)turn_tex, ImVec2(70, 70));
				ImGui::SetCursorPos(ImVec2(8, 0));

				if (ImGui::Button("Restart")) {
					gameStart = !gameStart;
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"最多翻棋")) {
					//Game.AIplace();
				}
				if (ImGui::Button("Pass")) {
					Game.nextTurn();
				}
				ImGui::SameLine();
				if (ImGui::Button("Surrender")) {
					//Game.gameover(-Game.getTurn());
				}
				ImGui::PushItemWidth(150);
				ImGui::SliderFloat("BGM Volume", &device.masterVolumeFactor, 0.0f, 1.0f);

				string tmp;
				if (Game.isSelecting)
					tmp = u8"isSelecting = true";
				else
					tmp = u8"isSelecting = false";

				ImGui::Text(tmp.c_str());
				tmp = u8"白子數量: ";
				ImGui::Text(tmp.c_str());
				ImGui::NewLine();

				if (Game.isOver()) {
					string win;
					GLint tex = 0;

					switch (Game.showWinner())
					{
					case Color::Black:
						win += u8"黑子獲勝!!!";
						tex = black_texture;
						break;
					case Color::White:
						win += u8"白子獲勝!!!";
						tex = white_texture;
						break;
					}
					ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
					ImGui::Begin("Winner", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoCollapse);
					ImGui::PopStyleColor();
					ImGui::Text(win.c_str());
					ImGui::Image((void*)(intptr_t)tex, ImVec2(70, 70));
					ImGui::End();
				}


				/*ImGui::SliderFloat("vertical", &dummy_size, 50.0f, 70.0f);
				ImGui::SliderFloat("horizontal", &space, 0.0f, 10.0f);*/

				//cout << Game.board->cell[0][0].getType();

				//	BOARD
				for (int i = 0; i < BOARD_SIZE; i++) {
					for (int j = 0; j < BOARD_SIZE; j++) {
						ImGui::PushID(i * BOARD_SIZE + j);
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(space, 0));
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

						/*if (i % 3 == 0) {
							if (ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.89, 0.87, 0.61, 50))) {
								Game.click(i, j);
							}
						}
						else if (i % 3 == 1) {
							if (ImGui::ImageButton((void*)(intptr_t)b_texture[0], ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.8, 0, 0, 50))) {
								Game.click(i, j);
							}
						}
						else if (i % 3 == 2) {
							if (ImGui::ImageButton((void*)(intptr_t)w_texture[0], ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.72, 0.84, 1, 50))) {
								Game.click(i, j);
							}
						}*/


						//fixing
						if (Game.isSelecting && Game.isMoveable(i, j)) {
							if (Game.board->cell[i][j].isEmpty) {
								if (ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.5, 0.5, 0.5, 50))) {
									Game.click(i, j);
								}
							}
							else if (Game.board->cell[i][j].getColor() == Color::Black) {
								if (ImGui::ImageButton((void*)(intptr_t)(b_texture[Game.board->cell[i][j].getType()]), ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.5, 0.5, 0.5, 50))) {
									Game.click(i, j);
								}
							}
							else if (Game.board->cell[i][j].getColor() == Color::White) {
								if (ImGui::ImageButton((void*)(intptr_t)w_texture[Game.board->cell[i][j].getType()], ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.5, 0.5, 0.5, 50))) {
									Game.click(i, j);
								}
							}
						}
						else {
							if (Game.board->cell[i][j].isEmpty) {
								if (ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(button_size, button_size))) {
									Game.click(i, j);
								}
							}
							else if (Game.board->cell[i][j].getColor() == Color::Black) {
								if (ImGui::ImageButton((void*)(intptr_t)(b_texture[Game.board->cell[i][j].getType()]), ImVec2(button_size, button_size))) {
									Game.click(i, j);
								}
							}
							else if (Game.board->cell[i][j].getColor() == Color::White) {
								if (ImGui::ImageButton((void*)(intptr_t)w_texture[Game.board->cell[i][j].getType()], ImVec2(button_size, button_size))) {
									Game.click(i, j);
								}
							}


							//else if (Game.board->cell[i][j].canMove()) {
							//	if (ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(button_size, button_size), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.5, 0.5, 0.5, 50))) {
							//		//Game.place(i, j);
							//	}
							//	if (ImGui::IsItemHovered()) {
							//		//ImGui::SetTooltip("Flip count:%d", Game.showFlips(i, j));
							//	}
							//}
							/*else {
								ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(button_size, button_size));
							}*/
						}

						/*else if (Game.board[i][j].color() == Color::EMPTY)
							if (Game.board[i][j].canMove())
								ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.5, 0.5, 0.5, 50));
							else
								ImGui::ImageButton((void*)(intptr_t)empty_texture, ImVec2(50, 50));*/
						ImGui::SameLine();
						ImGui::PopStyleVar();
						ImGui::PopStyleColor();
						ImGui::PopID();
					}
					ImGui::Dummy(ImVec2(1.0f, dummy_size));
				}
				//Game.UpdateFrame();
			}
			else {
				ImGui::SetCursorPos(ImVec2(90, 30));
				if (ImGui::Button(u8"雙人開始", ImVec2(100, 50))) {
					Game.start();
					gameStart = !gameStart;
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"AI黑子", ImVec2(100, 50))) {
					Game.start(Color::Black);
					gameStart = !gameStart;
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"AI白子", ImVec2(100, 50))) {
					Game.start(Color::White);
					gameStart = !gameStart;
				}
			}

			ImGui::End();
		}


		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}