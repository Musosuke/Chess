#pragma once
#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H


class ViewManager
{
public:

	ViewManager();
	~ViewManager();
	int Init();
	int Update();
	int ShouldCloseWindow();
private:
};



#endif // VIEWMANAGER_H