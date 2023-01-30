#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_Input_system = nullptr;
InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
	InputSystem::m_Input_system = nullptr;
}

void InputSystem::addListener(InputListener* listener)
{
	m_map_Listener.insert(std::make_pair<InputListener*, InputListener*>
			(std::forward<InputListener*>(listener),
			std::forward<InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_Listener.find(listener);
	if(it!=m_map_Listener.end())
	{
		m_map_Listener.erase(it);
	}
}

void InputSystem::update()
{
	// CURRENT MOUSE POS
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	// IF IT IS FIRST TIME THEN CHANGE IT
	if (m_first_time)
	{
		m_old_mouse_pos = point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;

	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		std::map<InputListener*, InputListener*>::iterator it = m_map_Listener.begin();
		while (it != m_map_Listener.end())
		{
			it->second->OnMouseMove(point(current_mouse_pos.x , current_mouse_pos.y));
			++it;
		}
	}

	// UPDATE FOR NEXT TIME
	m_old_mouse_pos = point(current_mouse_pos.x, current_mouse_pos.y);

	if(::GetKeyboardState(m_Keys_statep))
	{
		for(unsigned int i =0;i<255;++i)
		{
			if(m_Keys_statep[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator it = m_map_Listener.begin();
				while(it != m_map_Listener.end())
				{
					if(i==VK_LBUTTON)
					{
						if (m_Keys_statep[i] != m_old_Keys_stat[i])
						{
							it->second->OnLeftMouseDown(point(current_mouse_pos.x, current_mouse_pos.y));
						}
						
					}
					else if (i == VK_RBUTTON)
					{
						if (m_Keys_statep[i] != m_old_Keys_stat[i])
						{
							it->second->OnRightMouseDown(point(current_mouse_pos.x, current_mouse_pos.y));
						}

					}
					else
						it->second->onKeyDown(i);
					++it;
				}
			}
			else // key is up
			{
				if(m_Keys_statep[i]!=m_old_Keys_stat[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = m_map_Listener.begin();
					while (it != m_map_Listener.end())
					{
						if (i == VK_LBUTTON)
							it->second->OnLeftMouseUp(point(current_mouse_pos.x, current_mouse_pos.y));
						else if(i == VK_RBUTTON)
							it->second->OnRightMouseUp(point(current_mouse_pos.x, current_mouse_pos.y));
						else
							it->second->onKeyUp(i);
						++it;
					}
				}
			}
		}
		//store current keys state to old keys state buffer
		::memcpy(m_old_Keys_stat, m_Keys_statep, sizeof(unsigned char) * 256);

	}
}

void InputSystem::setCurserPosition(const point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::ShowCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::Get()
{
	static  InputSystem system;
	return &system;
}

void InputSystem::create()
{
	if (InputSystem::m_Input_system) throw std::exception("Input system is already created.");
	InputSystem::m_Input_system = new InputSystem();


}

void InputSystem::release()
{
	if (InputSystem::m_Input_system) return;
	delete InputSystem::m_Input_system;

}
