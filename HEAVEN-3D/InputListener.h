#pragma once
#include "Point.h"
class InputListener
{
public:
	InputListener()
	{
		
	}
	~InputListener()
	{
		
	}

	// pure virtual callback function
	virtual void onKeyDown(int key) = 0;

	virtual void onKeyUp(int key) = 0;

	// mous move
	virtual  void OnMouseMove(const point& mouse_pos) = 0;

	virtual  void OnLeftMouseDown(const point& mouse_pos) = 0;
	virtual  void OnRightMouseDown(const point& mouse_pos) = 0;

	virtual  void OnLeftMouseUp(const point& mouse_pos) = 0;
	virtual  void OnRightMouseUp(const point& mouse_pos) = 0;




};