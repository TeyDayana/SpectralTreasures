#include "trap.h"

trap::trap()
{
}

// ��������� ���������� � ���, ���� �� ������������ �������.
bool trap::is_active()
{
	return active;
}

// ��������� �������.
void trap::activate()
{
	active = true;
}
