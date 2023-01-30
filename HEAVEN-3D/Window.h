#pragma once
#include <Windows.h>
#include "Graphics.h"
class Window
{
public:
	// initialize window
	Window();

	
	
	
	bool release() const;
	bool isRunning();
	// Release Window
	~Window();
	RECT getClientWindowRect();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

private:
	bool broadcast();
protected:
	HWND m_Hwnd;
	bool m_IsRunning;
	bool m_is_init = false;
};

