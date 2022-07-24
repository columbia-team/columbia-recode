#pragma once
#include <vector>
#include <string>

#include "../../m_base/m_base.hpp"
#include "../m_groupbox/group.hpp"

class Groupbox;
class Window : public Base {
public:

	// Constructor.
	Window(std::string m_Name, vec2_t* m_Pos, vec2_t m_Size, std::vector<std::string> m_WindowTabs = { }, int* m_Selected = 0);

	// Add groubox to window.
	void AddGroup(Groupbox* Groupbox);

	// Window position.
	vec2_t* m_WindowPosition;

	// Vector.
	std::vector<std::string> m_WindowTabs;

	// Current selected tab.
	int* m_Selected;

private:

	// Draw window.
	void Draw();

	// Init window.
	void Run();

	void InitTabs();
	void InitPosition();

	// Some additions.
	std::string m_Name;
	vec2_t m_Size;

	// Tab swithced.
	bool m_SetSwitch;

};