#include "field.h"
#include <random>

// ��������� �������� ���� � ����������� �� ������ ����.
void field::generate(int level)
{
	// �������� ����������� �������� ������.
	if (level < 1)
	{
		return;
	}

	clear_vectors();
	// ����������� � ��������� �������� ����.
	len_x = len_x_level_multiplicator * level;
	len_y = len_y_level_multiplicator * level;
	location.resize(len_y, std::vector<std::pair<cell_type, int>>(len_x,
		std::make_pair(cell_type::Empty, 0)));
	artifacts_left = generate_artifacts_amount(level);

	std::pair<int, int> cell;
	// ������������ ��������� ������� ���������� � ���������� �� ���������.
	for (int i = 0; i < artifacts_left; ++i)
	{
		cell = place_artifact();
		place_ghost_random(cell);

		// ������������ ��������� ������� ������� ��� ���������, ����� ���� �����������.
		if (ghosts[i]->get_type() != ghost_type::Confused)
		{
			place_trap();
		}
	}

	// ��������� ������ � ��������� ��������� ���������� ������ �������� ����, ���� ��������� ���� ������.
	if (!valid_cell(place_player()))
	{
		clear_vectors();
		generate(level);
	}
}

// ��������� ������� ���� (����� � ������).
std::pair<int, int> field::size()
{
	return std::make_pair(len_x, len_y);
}

// ����������� ������ � ����������� ����������� (�� 1 ������).
bool field::move_player(direction direction)
{
	if (direction != direction::None)
	{
		std::pair<int, int> cell = get_adjacent_cell(player_cell[0], player_cell[1], direction);
		if (valid_cell(cell) && empty_cell(cell))
		{
			// ���� ������ ��������, �� ����� ��������� � �������� �������������� � �������� �����.
			clear_cell(std::make_pair(player_cell[0], player_cell[1]));
			location[cell.second][cell.first] = std::make_pair(cell_type::Player, 0);
			player_cell[0] = cell.first;
			player_cell[1] = cell.second;
			return true;
		}
	}
	return false;
}

// ���� ��������� ���������� (����������� � ������� �� ������ ������).
void field::collect_artifacts()
{
	std::pair<int, int> cell;
	// �������� ������ ������ ������ (������, ������, �����, �����) �� ������� ���������� ����� �� ������.
	for (int i = 0; i < 4; ++i)
	{
		cell = get_adjacent_cell(player_cell[0], player_cell[1], static_cast<direction>(i));
		if (valid_cell(cell) && get_cell_type(cell) == cell_type::Artifact)
		{
			collect_artifact(cell);
		}
	}
}

// ��������� ��������� ������� (����������� � ������� �� ������ ������).
void field::activate_traps()
{
	std::pair<int, int> cell;
	// �������� ������ ������ ������ (������, ������, �����, �����) �� ������� ������� ����� �� ����������.
	for (int i = 0; i < 4; ++i)
	{
		cell = get_adjacent_cell(player_cell[0], player_cell[1], static_cast<direction>(i));
		if (valid_cell(cell) && get_cell_type(cell) == cell_type::Trap)
		{
			activate_trap(cell);
		}
	}
}

// ��������� ���������� � ��� �������, ������������� � ��������� ������.
cell_type field::get_cell_type(std::pair<int, int> cell)
{
	return location[cell.second][cell.first].first;
}

// ��������: ������� �� �������, ����������� � ������.
bool field::disabled_object(int x, int y)
{
	// ������� ������� (�������������) �� ��� ���, ���� �� ������.
	// ������� ������� (��������), ���� ����� � �����������.
	// �������� ������� (���������� �� ����) �� ��� ���, ���� �� ��� ���� �������.
	switch (get_cell_type(std::make_pair(x, y)))
	{
	case cell_type::Ghost:
		return ghosts[location[y][x].second]->is_trapped();
		break;

	case cell_type::Trap:
		return traps[location[y][x].second]->is_active();
		break;

	case cell_type::Artifact:
		return !artifacts[location[y][x].second]->is_valid();
		break;

	default:
		return false;
	}
}

// ��������� ������ ����� ����������, ����������� � ����� ��� ����������� ������.
int field::get_artifacts_total()
{
	return artifacts.size();
}

// ��������� ����� ��������� ����������.
int field::get_artifacts_collected()
{
	return get_artifacts_total() - artifacts_left;
}

// ��������� ����� ���������� ��� �� ��������� ����������.
int field::get_artifacts_left()
{
	return artifacts_left;
}

// �������� ������ �������� ���� �� ����������� �������������.
bool field::valid_cell(std::pair<int, int> cell)
{
	return cell.first >= 0 && cell.second >= 0 && cell.first < len_x&& cell.second < len_y;
}

// �������� ������ �������� ���� �� �����������.
bool field::empty_cell(std::pair<int, int> cell)
{
	return location[cell.second][cell.first].first == cell_type::Empty;
}

// �������� ������ �������� ���� �� ���������� ������ �� ������� ���������.
bool field::safe_cell(std::pair<int, int> cell)
{
	for (int i = 0; i < ghosts.size(); ++i)
	{
		if (ghosts[i]->can_see(cell.first, cell.second))
		{
			return false;
		}
	}
	return true;
}

// ��������� ��������� ������� ������ �� ������������ �����������.
std::pair<int, int> field::get_adjacent_cell(int x_curr, int y_curr, direction direction)
{
	switch (direction)
	{
	case direction::Ahead:
		return std::make_pair(x_curr, y_curr - 1);
	case direction::Back:
		return std::make_pair(x_curr, y_curr + 1);
	case direction::Right:
		return std::make_pair(x_curr + 1, y_curr);
	default:
		return std::make_pair(x_curr - 1, y_curr);
	}
}

// ������� ��������� ������.
void field::clear_cell(std::pair<int, int> cell)
{
	location[cell.second][cell.first].first = cell_type::Empty;
}

// ��������� ������� ��������, ������� ����� ������ ����������� ��������.
int field::get_ghost_to_trap(std::pair<int, int> trap_cell)
{
	// ���������� ������������ ���������� �� �������� �� ������ � �������� � ������� ����� ��������.
	int index = -1;
	double min_distance = len_x + len_y;
	double distance = min_distance;

	int dist_x, dist_y;
	std::pair<int, int> ghost_cell;
	// ���������� ��������� ���������� ������ ��� �� ��������� ��������� �� ���� �����������.
	for (int i = 0; i < ghosts.size(); ++i)
	{
		if (ghosts[i]->get_type() != ghost_type::Confused && !ghosts[i]->is_trapped())
		{
			ghost_cell = ghosts[i]->get_location();
			// ���������� ���� �������� �� �������� �� ������� �� ���� � � �. 
			dist_x = abs(ghost_cell.first - trap_cell.first);
			dist_y = abs(ghost_cell.second - trap_cell.second);

			// 1.7� -- ��������������� ������ ����� ������� �� ��������� � �� �����.
			if (dist_x * dist_y == 0)
			{
				distance = dist_x + 1.7 * dist_y;
			}
			else
			{
				// ���������� ���������� ��� ������ ������� ��������,
				//	���� ������ �� ����� �� ����� ��������������/������������ ������.
				distance = sqrt(dist_x * dist_x + 2.9 * dist_y * dist_y);
			}

			if (distance < min_distance)
			{
				min_distance = distance;
				index = i;
			}
		}
	}
	return index;
}

// ���� ��������� � ����������� ������.
void field::collect_artifact(std::pair<int, int> cell)
{
	clear_cell(cell);
	artifacts[location[cell.second][cell.first].second]->collect();
	--artifacts_left;
}

// ��������� ������� �� ������ � ���������������.
void field::activate_trap(std::pair<int, int> cell)
{
	// ������� ������������ � ����� ��������, ���� ��� �� ���� ������������.
	if (!traps[location[cell.second][cell.first].second]->is_active())
	{
		traps[location[cell.second][cell.first].second]->activate();
		ghosts[get_ghost_to_trap(cell)]->trap();
	}
}

int field::get_chasing_ghosts()
{
	return chasing_ghosts;
}

int field::get_scary_ghosts()
{
	return scary_ghosts;
}

// ���������� ���������� � �� ���.
void field::manage_ghosts()
{
	chasing_ghosts = 0;
	for (int i = 0; i < ghosts.size(); ++i)
	{
		if (!ghosts[i]->is_trapped())
		{
			if (ghosts[i]->can_see(player_cell[0], player_cell[1]))
			{
				ghost_chase_turn(i);
				++chasing_ghosts;
			}
			else if (ghosts[i]->get_type() != ghost_type::Defender)
			{
				ghost_patrol_turn(i);
			}
		}
	}
	ghosts_scare();
}

// ��� �������� -- ������������� ������.
void field::ghost_chase_turn(int ghost_idx)
{
	std::pair<int, int> curr_cell = ghosts[ghost_idx]->get_location();
	// ���������� ���������� ������ �� �������� �� ������ ����� � ������.
	int up_distance = curr_cell.second - player_cell[1];
	int right_distance = player_cell[0] - curr_cell.first;

	if (!(abs(up_distance) == 1 && right_distance == 0) && !(abs(right_distance) == 1 && up_distance == 0))
	{
		bool moved;
		direction dir;
		do
		{
			moved = true;
			// ����������� �������� � ������� � ������ �� ��������� ��� ����������� -- ���� ������.
			if (abs(up_distance) >= abs(right_distance))
			{
				if (up_distance > 0)
				{
					dir = direction::Ahead;
				}
				else
				{
					dir = direction::Back;
				}
			}
			else
			{
				if (right_distance > 0)
				{
					dir = direction::Right;
				}
				else
				{
					dir = direction::Left;
				}
			}

			// ��� ������������� ���� �� ���������� �����������, ��� � ������, ���������� � �������, �������.
			if (!move_ghost(ghost_idx, dir))
			{
				moved = false;
				if (dir == direction::Ahead || dir == direction::Back)
				{
					up_distance = 0;
				}
				else
				{
					right_distance = 0;
				}
			}
		} while (!moved);
	}
}

// ��� �������� -- �������������� ����������.
void field::ghost_patrol_turn(int ghost_idx)
{
	std::pair<int, int> curr_cell = ghosts[ghost_idx]->get_location();
	std::pair<int, int> move_point;
	direction dir;

	std::default_random_engine re(random());
	std::uniform_int_distribution<int> rd(0, 3);
	for (int j = 0; j < 10; ++j)
	{
		switch (rd(re))
		{
		case 0:
			dir = direction::Ahead;
			break;

		case 1:
			dir = direction::Back;
			break;

		case 2:
			dir = direction::Right;
			break;

		default:
			dir = direction::Left;
			break;
		}

		move_point = get_adjacent_cell(curr_cell.first, curr_cell.second, dir);
		if (ghosts[ghost_idx]->can_patrol(move_point) && move_ghost(ghost_idx, dir))
		{
			break;
		}
	}
}

// ����������� ������ ���������� ������.
void field::ghosts_scare()
{
	scary_ghosts = 0;
	std::default_random_engine re(random());
	std::uniform_int_distribution<int> rd(0, 3);

	std::pair<int, int> cell;
	for (int i = 0; i < 4; ++i)
	{
		cell = get_adjacent_cell(player_cell[0], player_cell[1], static_cast<direction>(i));
		if (valid_cell(cell) && get_cell_type(cell) == cell_type::Ghost
			&& !ghosts[location[cell.second][cell.first].second]->is_trapped())
		{
			if (rd(re) == 0)
			{
				++scary_ghosts;
			}
		}
	}
}

// ����������� ������������ �������� � ��������� ����������� (�� 1 ������).
bool field::move_ghost(int idx, direction direction)
{
	std::pair<int, int> cell = ghosts[idx]->get_location();
	std::pair<int, int> new_cell = get_adjacent_cell(cell.first, cell.second, direction);
	if (valid_cell(new_cell) && empty_cell(new_cell))
	{
		// ���� ������ ��������, �� ������� ��������� � �������� �������������� � �������� �����.
		clear_cell(cell);
		location[new_cell.second][new_cell.first] = std::make_pair(cell_type::Ghost, idx);
		ghosts[idx]->set_location(new_cell);
		return true;
	}
	return false;
}

// ��������� ��������� � ��������� ������.
std::pair<int, int> field::place_artifact()
{
	std::pair<int, int> cell = get_random_empty_cell();
	artifacts.push_back(std::unique_ptr<artifact>(new artifact()));
	location[cell.second][cell.first] = std::make_pair(cell_type::Artifact, artifacts.size() - 1);
	return cell;
}

// ��������� �������� ���������� ���� ����� ������������ ���������.
std::pair<int, int> field::place_ghost_random(std::pair<int, int> artifact_cell)
{
	std::default_random_engine re(random());
	std::uniform_int_distribution<int> rd(0, 2);
	// �������� ������� �������� ���������� ���� � ���������� ��� � ������ ���������.
	// 0 -- ��� �������, 1 -- ��� ��������, 2 -- ��� �����������.
	switch (rd(re))
	{
	case 0:
	{
		ghosts.push_back(std::unique_ptr<ghost>(new dangerous
		(len_x, len_y, artifact_cell.first, artifact_cell.second)));
	}
	break;

	case 1:
	{
		ghosts.push_back(std::unique_ptr<ghost>(new defender
		(len_x, len_y, artifact_cell.first, artifact_cell.second)));
	}
	break;

	case 2:
	{
		ghosts.push_back(std::unique_ptr<ghost>(new confused(len_x, len_y)));
	}
	break;
	}
	int index = ghosts.size() - 1;

	std::pair<int, int> cell;
	// ��������� ���������� �������� � ���� ��������������.
	do
	{
		cell = ghosts[index]->place();
	} while (!empty_cell(cell));
	location[cell.second][cell.first] = std::make_pair(cell_type::Ghost, index);
	return cell;
}

// ��������� ������� � ��������� ������.
std::pair<int, int> field::place_trap()
{
	std::pair<int, int> cell = get_random_empty_cell();
	traps.push_back(std::unique_ptr<trap>(new trap()));
	location[cell.second][cell.first] = std::make_pair(cell_type::Trap, traps.size() - 1);
	return cell;
}

// ��������� ������ � ��������� ���������� ������ �� ������� ����.
std::pair<int, int> field::place_player()
{
	std::pair<int, int> cell;
	for (int i = 0; i < 100; ++i)
	{
		cell = get_random_empty_cell();
		// ��� ���������� ������ � ��������� ������ ������, ����� ���������� ����.
		if (safe_cell(cell))
		{
			location[cell.second][cell.first] = std::make_pair(cell_type::Player, 0);
			player_cell[0] = cell.first;
			player_cell[1] = cell.second;
			return cell;
		}
	}
	return std::make_pair(-1, -1);
}

// ��������� ����� ���������� (� ���������) �� ������� ���� � ����������� �� ������.
int field::generate_artifacts_amount(int level)
{
	int pre_artifacts_amount = round((0.02 - 0.00001 * (level - 1)) * len_x * len_y);
	std::default_random_engine re(random());
	std::uniform_real_distribution<double> rd_aa(0.8 * pre_artifacts_amount, pre_artifacts_amount);
	return round(rd_aa(re));
}

// ��������� ��������� ��������� ������ �� ������� ����.
std::pair<int, int> field::get_random_empty_cell()
{
	int x, y;
	std::default_random_engine re(random());
	// ��� ��������� ����� � �������� ���������� �������� (����� � ������ ����).
	std::uniform_int_distribution<int> rd_x(0, len_x - 1);
	std::uniform_int_distribution<int> rd_y(0, len_y - 1);

	std::pair<int, int> cell;
	// ��������� ��������� ��������� �������� ���� �� ���������� ���������.
	do
	{
		cell.first = rd_x(re);
		cell.second = rd_y(re);
	} while (!empty_cell(cell));
	return cell;
}

// �������� ��������� �� �������� ����������, ���������, ������� � �������� ����.
void field::clear_vectors()
{
	artifacts.clear();
	ghosts.clear();
	traps.clear();
	location.clear();
}
