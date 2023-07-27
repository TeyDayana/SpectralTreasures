#pragma once
#include "artifact.h"
#include "trap.h"
#include "ghost.h"
#include <random>
#include <vector>
#include <memory>

enum class cell_type { Empty, Artifact, Ghost, Trap, Player };

enum class direction { Ahead = 0, Back = 1, Right = 2, Left = 3, None = 4 };

class field
{
private:
	int len_x;
	int len_y;
	int player_cell[2] = { -1, -1 };

	// Объект для генерации случайных чисел.
	std::random_device random;
	int len_x_level_multiplicator = 8;
	int len_y_level_multiplicator = 4;

	// Представление игрового поля в виде матрицы пар и массивов объектов (артефакты, ловушки, призраки):
	//	тип объекта и его индекс в массиве объектов этого типа.
	std::vector<std::vector<std::pair<cell_type, int>>> location;
	std::vector<std::unique_ptr<artifact>> artifacts;
	std::vector<std::unique_ptr<trap>> traps;
	std::vector<std::unique_ptr<ghost>> ghosts;

	int artifacts_left = 0;
	int chasing_ghosts = 0;
	int scary_ghosts = 0;

	// Функции, используемые для работы с клетками поля.
	bool valid_cell(std::pair<int, int> cell);
	bool empty_cell(std::pair<int, int> cell);
	bool safe_cell(std::pair<int, int> cell);
	std::pair<int, int> get_adjacent_cell(int x, int y, direction direction);
	void clear_cell(std::pair<int, int> cell);

	// Функции, используемые в реализации хода игрока.
	void collect_artifact(std::pair<int, int> cell);
	void activate_trap(std::pair<int, int> cell);
	int get_ghost_to_trap(std::pair<int, int> trap_cell);

	// Функции, используемые в реализации ходов призраков.
	void ghost_chase_turn(int ghost_idx);
	void ghost_patrol_turn(int ghost_idx);
	void ghosts_scare();
	bool move_ghost(int idx, direction direction);

	// Функции, используемые при генерации игрового поля.
	std::pair<int, int> get_random_empty_cell();
	int generate_artifacts_amount(int level);
	void clear_vectors();

	// Функции, используемые при генерации игрового поля: расставление объектов.
	std::pair<int, int> place_artifact();
	std::pair<int, int> place_ghost_random(std::pair<int, int> artifact_cell);
	std::pair<int, int> place_trap();
	std::pair<int, int> place_player();

public:
	void generate(int level);
	cell_type get_cell_type(std::pair<int, int> cell);
	bool disabled_object(int x, int y);
	std::pair<int, int> size();

	bool move_player(direction direction);
	void collect_artifacts();
	void activate_traps();

	int get_artifacts_total();
	int get_artifacts_collected();
	int get_artifacts_left();
	int get_chasing_ghosts();
	int get_scary_ghosts();

	void manage_ghosts();
};

