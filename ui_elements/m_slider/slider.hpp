#pragma once
#include "../m_groupbox/group.hpp"

class slider_new : public Base {
public:

	// Constructor.
	slider_new(std::string m_Name, float* m_Value, int m_Min = 0, int m_Max = 100, std::string m_Suffix = "");

	void Draw();
	void Update();

	vec2_t m_Pos;
	bool m_AllowDraw;

private:

	std::string m_Name;
	std::string m_Suffix;

	float* m_Value;

	int m_Min;
	int m_Max;

};