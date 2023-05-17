#pragma once
#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H



#define BOARD_SIZE 8

class ViewManager
{
public:

	ViewManager();
	~ViewManager();
	int Init();
	int Update();
	int ShouldCloseWindow();
private:
	int my_image_width = 0;
	int my_image_height = 0;
	float button_size = 45;
	float dummy_size = 54.8;
	float space = 5.1;
};



#endif // VIEWMANAGER_H