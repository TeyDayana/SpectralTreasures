#pragma once
#include "player.h"
#include "field.h"
#include "view.h"

class game
{
private:
	view view;
	int ghosts_chasing = 0;
	int ghosts_begin_chase = 0;
	int loses = 0;
	void player_turn_mechanics();
	
public:
	bool player_turn();
	void ghost_turns();
	void player_take_damage();
	void print();
	void print_warnings();

	void generate_field();
	void level_up();
	bool game_over();
	void finish();

	bool is_game_over();
	bool is_finished();
	bool goals_achieved();

	player player;
	int level = 1;
	field field;
};
