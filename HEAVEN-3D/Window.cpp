#include "Window.h"
#include <exception>

//Window* window = nullptr;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{

		break;
	}
	case WM_DESTROY:
	{//destroy event
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);

		break;
	}
	case WM_SETFOCUS:
	{
		//window focus event
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if(window)window->onFocus();
				
		break;
	}
	case WM_KILLFOCUS:
	{
		//window focus event
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}
	default:
	{
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	}

	return NULL;
}

Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"WINDOW";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
	// call wind32 funcrion
	// failing of registration of class returns false
	if (!::RegisterClassEx(&wc))
	{
		throw std::exception("Window not created successfully.");
	}

	
	m_Hwnd = ::CreateWindowEx
	(WS_EX_OVERLAPPEDWINDOW,
		L"WINDOW", 
		L"HEAVEN3D",
		WS_CAPTION|WS_SYSMENU, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		1024,
		768,
		NULL,
		NULL,
		NULL,
		NULL);

	// if handle failse return false;
	if (!m_Hwnd)
		throw std::exception("handle not created successfully.");


	// show the window
	::ShowWindow(m_Hwnd, SW_SHOW);
	::UpdateWindow(m_Hwnd);

	m_IsRunning = true;

	
}


bool Window::broadcast()
{
	MSG msg;
	if(!this->m_is_init)
	{
		// create event
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);
		
		this->onCreate();
		this->m_is_init = true;
	}

	this->onUpdate();
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// to prevent cpu from throttling
	Sleep(1);

	return true;
}



bool Window::isRunning()
{
	if(m_IsRunning)broadcast();
	return m_IsRunning;
}

Window::~Window()
{

}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_Hwnd, &rc);
	return rc;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_IsRunning = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}



