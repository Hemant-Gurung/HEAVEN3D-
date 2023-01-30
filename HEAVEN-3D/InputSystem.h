#pragma once
#include "InputListener.h"
#include <map>

class point;
class InputSystem
{
private:
	InputSystem();
	~InputSystem() ;

public:
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();
	void setCurserPosition(const point& pos);
	void ShowCursor(bool show);
public:
	static InputSystem* Get();
	static  void create();
	static  void release();
private:
	std::map<InputListener*, InputListener*> m_map_Listener;
	unsigned char m_Keys_statep[256] = {};
	unsigned char m_old_Keys_stat[256] = {};
	point m_old_mouse_pos;
	bool m_first_time = true;
	static InputSystem* m_Input_system;;

};

