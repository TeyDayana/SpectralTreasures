#include "game.h"

// ���������� ���� ������.
bool game::player_turn()
{
	view.print_make_turn();
	direction direction = direction::None;
	do
	{
		switch (view.get_input())
		{
		case 'w':
			direction = direction::Ahead;
			break;

		case 's':
			direction = direction::Back;
			break;

		case 'd':
			direction = direction::Right;
			break;

		case 'a':
			direction = direction::Left;
			break;

		case ' ':
			player_turn_mechanics();
			return true;

		case 27:
			return false;

		default:
			direction = direction::None;
		}
	} while (!field.move_player(direction));
	player_turn_mechanics();
	return true;
}

// ���� ���������� � ��������� ������� ����������.
void game::player_turn_mechanics()
{
	field.collect_artifacts();
	field.activate_traps();
}

// ���������� ����� ���������.
void game::ghost_turns()
{
	field.manage_ghosts();
}

void game::player_take_damage()
{
	ghosts_begin_chase = field.get_chasing_ghosts() - ghosts_chasing;
	ghosts_chasing = field.get_chasing_ghosts();

	if (!field.get_scary_ghosts())
	{
		loses = 0;
	}
	else
	{
		if (field.get_scary_ghosts() <= ghosts_chasing - ghosts_begin_chase)
		{
			loses = field.get_scary_ghosts();
		}
		else
		{
			loses = ghosts_chasing - ghosts_begin_chase;
		}
		player.get_bitten(loses);
	}
}

// ����� ��������� ����: ���� � ��������������.
void game::print()
{
	view.clear_console();
	view.print_level(level);
	view.print_field(field);
	view.print_lives(player.get_health(), player.get_max_health());
	view.print_artifacts_collected(field.get_artifacts_collected(), field.get_artifacts_total());
	view.print_empty_line();
}

void game::print_warnings()
{
	if (ghosts_chasing > 0 && !goals_achieved())
	{
		if (ghosts_begin_chase > 0)
		{
			view.print_ghosts_begin_chase(ghosts_begin_chase);
		}
		view.print_ghosts_chasing(ghosts_chasing);

		if (loses > 0)
		{
			view.print_loses(loses);
		}
	}
}

// ��������� �������� ���� ���� �������� ������.
void game::generate_field()
{
	field.generate(level);
	ghosts_chasing = 0;
	ghosts_begin_chase = 0;
}

void game::level_up()
{
	level = player.level_up();
	if (level <= 5)
	{
		view.level_up();
	}
}

bool game::game_over()
{
	if (view.game_over(level))
	{
		return true;
	}
	player.rebirth();
	return false;
}

void game::finish()
{
	view.finish();
}

// �������� �� �������� (���� �� �����).
bool game::is_game_over()
{
	return !player.is_alive();
}

bool game::is_finished()
{
	return level > 5;
}

// ��������: ������� �� ������� (������� ��� ���������).
bool game::goals_achieved()
{
	return !field.get_artifacts_left();
}
