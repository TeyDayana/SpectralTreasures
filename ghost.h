#pragma once
#include <vector>
#include <string>

enum class ghost_type { Dangerous = 0, Defender = 1, Confused = 2 };

class ghost
{
protected:
	ghost_type type;
	int cell[2] = { -1, -1 };
	int visibility_radius_y = 0;
	bool trapped = false;

	virtual void init_patrol_zone();
	//  оординаты-границы зоны патрулировани€ призрака.
	int patrol_x1 = 0;
	int patrol_x2 = 0;
	int patrol_y1 = 0;
	int patrol_y2 = 0;

public:
	ghost();
	std::pair<int, int> place();
	void set_location(std::pair<int, int> new_cell);

	bool can_see(int x, int y);
	bool can_patrol(std::pair<int, int> cell);
	void trap();

	ghost_type get_type();
	bool is_trapped();
	std::pair<int, int> get_location();
};

class dangerous : public ghost
{
private:
	void init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y);
public:
	dangerous(int len_x, int len_y, int artifact_x, int artifact_y);
};

class defender : public ghost
{
private:
	void init_patrol_zone(int len_x, int len_y, int artifact_x, int artifact_y);
public:
	defender(int len_x, int len_y, int artifact_x, int artifact_y);
};

class confused : public ghost
{
private:
	void init_patrol_zone(int len_x, int len_y);
public:
	confused(int len_x, int len_y);
};
