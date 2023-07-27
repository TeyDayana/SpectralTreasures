#include "ghost.h"
#include <random>

ghost::ghost()
{
}

void ghost::init_patrol_zone()
{
}

// ��������� �������� �� ��������� ������ �������� ���� � ���� ��� ��������������.
std::pair<int, int> ghost::place()
{
	std::random_device r;
	std::default_random_engine re(r());
	std::uniform_int_distribution<int> rd_x(patrol_x1, patrol_x2);
	std::uniform_int_distribution<int> rd_y(patrol_y1, patrol_y2);

	std::pair<int, int> cell;
	// ��������� ��������� ������ � �������� ������ �������.
	cell.first = rd_x(re);
	cell.second = rd_y(re);
	set_location(cell);
	return cell;
}

// ��������� ��������� �������������� ��������.
void ghost::set_location(std::pair<int, int> new_cell)
{
	cell[0] = new_cell.first;
	cell[1] = new_cell.second;
}

// ��������� ���������� � ���, ������ �� �������.
bool ghost::is_trapped()
{
	return trapped;
}

// ��������� ��������� ������ ��������������� ��������.
std::pair<int, int> ghost::get_location()
{
	return std::make_pair(cell[0], cell[1]);
}

// ������������� �������� ���� ������� � ��� ���� �������.
dangerous::dangerous(int len_x, int len_y, int artifact_x, int artifact_y)
{
	type = ghost_type::Dangerous;
	visibility_radius_y = 2;
	init_patrol_zone(len_x, len_y, artifact_x, artifact_y);
}

// ������������� ���������-������ ���������� ���� ��� �������� ���� �������.
void dangerous::init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y)
{
	int i;
	// ���������� ����� �������, ���������� � �������� �������� ����.
	for (i = 4; artifact_x - i < 0; --i) {
	}
	patrol_x1 = artifact_x - i;

	// ���������� ������� �������, ���������� � �������� �������� ����.
	for (i = 2; artifact_y - i < 0; --i) {
	}
	patrol_y1 = artifact_y - i;

	// ���������� ������ �������, ���������� � �������� �������� ����.
	for (i = 4; artifact_x + i >= len_x; --i) {
	}
	patrol_x2 = artifact_x + i;

	// ���������� ������ �������, ���������� � �������� �������� ����.
	for (i = 2; artifact_y + i >= len_y; --i) {
	}
	patrol_y2 = artifact_y + i;
}

// ������������� �������� ���� �������� � ��� ���� �������.
defender::defender(int len_x, int len_y, int artifact_x, int artifact_y)
{
	type = ghost_type::Defender;
	visibility_radius_y = 3;
	init_patrol_zone(len_x, len_y, artifact_x, artifact_y);
}

// ������������� ���������-������ ���������� ���� ��� �������� ���� ��������.
void defender::init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y)
{
	int i;
	// ���������� ����� �������, ���������� � �������� �������� ����.
	for (i = 1; artifact_x - i < 0; --i) {
	}
	patrol_x1 = artifact_x - i;

	// ���������� ������� �������, ���������� � �������� �������� ����.
	for (i = 1; artifact_y - i < 0; --i) {
	}
	patrol_y1 = artifact_y - i;

	// ���������� ������ �������, ���������� � �������� �������� ����.
	for (i = 1; artifact_x + i >= len_x; --i) {
	}
	patrol_x2 = artifact_x + i;

	// ���������� ������ �������, ���������� � �������� �������� ����.
	for (i = 1; artifact_y + i >= len_y; --i) {
	}
	patrol_y2 = artifact_y + i;
}

// ������������� �������� ���� ����������� � ��� ���� �������.
confused::confused(int len_x, int len_y)
{
	type = ghost_type::Confused;
	visibility_radius_y = 1;
	init_patrol_zone(len_x, len_y);
}

// ������������� ���������-������ ���������� ���� ��� �������� ���� �����������.
void confused::init_patrol_zone(int len_x, int len_y)
{
	// �������������� ����� �������� ����.
	patrol_x1 = 0;
	patrol_y1 = 0;
	patrol_x2 = len_x - 1;
	patrol_y2 = len_y - 1;
}

bool ghost::can_see(int x, int y)
{
	return x >= (cell[0] - 2 * visibility_radius_y) && x <= (cell[0] + 2 * visibility_radius_y)
		&& y >= (cell[1] - visibility_radius_y) && y <= (cell[1] + visibility_radius_y);
}

bool ghost::can_patrol(std::pair<int, int> cell)
{
	return cell.first >= patrol_x1 && cell.first <= patrol_x2
		&& cell.second >= patrol_y1 && cell.second <= patrol_y2;
}

// ��������� � �������.
void ghost::trap()
{
	trapped = true;
}

// ��������� ���� ��������.
ghost_type ghost::get_type()
{
	return type;
}
