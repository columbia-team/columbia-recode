#pragma once
#include "../m_groupbox/group.hpp"

class Combo : public Base
{
public:

	Combo(std::string m_Name, int* m_Value, std::vector<std::string> m_Items);

	void Update();
	void Draw();
	void DrawBox();

	vec2_t m_Pos;
	bool m_Focused;

private:

	std::string m_Name;
	int* m_Value;

	std::vector<std::string> m_Items;
};