#pragma once
#include "../m_groupbox/group.hpp"

class checkbox_new : public Base {
public:

	// Constructor.
	checkbox_new(std::string m_Name, bool* m_Value);

	void Draw();
	void Update();

	vec2_t m_Pos;

private:

	std::string m_Name;
	bool* m_Value;
};