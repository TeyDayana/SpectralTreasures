#include "ghost.h"
#include <random>

ghost::ghost()
{
}

void ghost::init_patrol_zone()
{
}

// ѕомещение призрака на случайную клетку игрового пол€ в зону его патрулировани€.
std::pair<int, int> ghost::place()
{
	std::random_device r;
	std::default_random_engine re(r());
	std::uniform_int_distribution<int> rd_x(patrol_x1, patrol_x2);
	std::uniform_int_distribution<int> rd_y(patrol_y1, patrol_y2);

	std::pair<int, int> cell;
	// √енераци€ координат клеток в пределах границ патрул€.
	cell.first = rd_x(re);
	cell.second = rd_y(re);
	set_location(cell);
	return cell;
}

// ”становка координат местоположени€ призрака.
void ghost::set_location(std::pair<int, int> new_cell)
{
	cell[0] = new_cell.first;
	cell[1] = new_cell.second;
}

// ѕолучение информации о том, пойман ли призрак.
bool ghost::is_trapped()
{
	return trapped;
}

// ѕолучение координат клетки местонахождени€ призрака.
std::pair<int, int> ghost::get_location()
{
	return std::make_pair(cell[0], cell[1]);
}

// »нициализаци€ призрака типа ќпасный и его зоны патрул€.
dangerous::dangerous(int len_x, int len_y, int artifact_x, int artifact_y)
{
	type = ghost_type::Dangerous;
	visibility_radius_y = 2;
	init_patrol_zone(len_x, len_y, artifact_x, artifact_y);
}

// »нициализаци€ координат-границ патрульной зоны дл€ призрака типа ќпасный.
void dangerous::init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y)
{
	int i;
	// Ќахождение левой границы, допустимой в пределах игрового пол€.
	for (i = 4; artifact_x - i < 0; --i) {
	}
	patrol_x1 = artifact_x - i;

	// Ќахождение верхней границы, допустимой в пределах игрового пол€.
	for (i = 2; artifact_y - i < 0; --i) {
	}
	patrol_y1 = artifact_y - i;

	// Ќахождение правой границы, допустимой в пределах игрового пол€.
	for (i = 4; artifact_x + i >= len_x; --i) {
	}
	patrol_x2 = artifact_x + i;

	// Ќахождение нижней границы, допустимой в пределах игрового пол€.
	for (i = 2; artifact_y + i >= len_y; --i) {
	}
	patrol_y2 = artifact_y + i;
}

// »нициализаци€ призрака типа «ащитник и его зоны патрул€.
defender::defender(int len_x, int len_y, int artifact_x, int artifact_y)
{
	type = ghost_type::Defender;
	visibility_radius_y = 3;
	init_patrol_zone(len_x, len_y, artifact_x, artifact_y);
}

// »нициализаци€ координат-границ патрульной зоны дл€ призрака типа «ащитник.
void defender::init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y)
{
	int i;
	// Ќахождение левой границы, допустимой в пределах игрового пол€.
	for (i = 1; artifact_x - i < 0; --i) {
	}
	patrol_x1 = artifact_x - i;

	// Ќахождение верхней границы, допустимой в пределах игрового пол€.
	for (i = 1; artifact_y - i < 0; --i) {
	}
	patrol_y1 = artifact_y - i;

	// Ќахождение правой границы, допустимой в пределах игрового пол€.
	for (i = 1; artifact_x + i >= len_x; --i) {
	}
	patrol_x2 = artifact_x + i;

	// Ќахождение нижней границы, допустимой в пределах игрового пол€.
	for (i = 1; artifact_y + i >= len_y; --i) {
	}
	patrol_y2 = artifact_y + i;
}

// »нициализаци€ призрака типа –астер€нный и его зоны патрул€.
confused::confused(int len_x, int len_y)
{
	type = ghost_type::Confused;
	visibility_radius_y = 1;
	init_patrol_zone(len_x, len_y);
}

// »нициализаци€ координат-границ патрульной зоны дл€ призрака типа –астер€нный.
void confused::init_patrol_zone(int len_x, int len_y)
{
	// ѕатрулирование всего игрового пол€.
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

// ѕопадание в ловушку.
void ghost::trap()
{
	trapped = true;
}

// ѕолучение типа призрака.
ghost_type ghost::get_type()
{
	return type;
}
