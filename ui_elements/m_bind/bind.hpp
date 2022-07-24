#pragma once
#include "../m_groupbox/group.hpp"

class bind_new : public Base {
public:

	bind_new(int* m_Value, int* m_BindType);

	void Update();
	void Draw();

	void UpdateList();
	void InitList();

	vec2_t m_Pos;

private:

	int* m_Value;
	int* m_BindType;

	bool m_Focused;
	bool m_FocusedList;
};