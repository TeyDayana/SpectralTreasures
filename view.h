#pragma once
#include "field.h"

class view
{
private:
	void print_object(cell_type type, bool disabled);
	void print_horizontal_border(int length);

public:
	void print_field(field& field);
	void print_level(int level);
	void print_lives(int current, int total);
	void print_artifacts_collected(int collected, int total);

	void print_ghosts_begin_chase(int amount);
	void print_ghosts_chasing(int amount);
	void print_loses(int amount);

	void level_up();
	bool game_over(int level);
	void finish();

	int get_input();
	void print_make_turn();
	void print_empty_line();
	void clear_console();
};
