#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "view.h"

// ����� ����������� ������� �������� ���� �� �����.
void view::print_field(field& field)
{
	// ��������� ������� ����.
	std::pair<int, int> size = field.size();
	print_horizontal_border(size.first + 2);
	// ���������� ����� ������� ���� ������ �������� �� ������ ������ (��� ������).
	for (int i = 0; i < size.second; ++i)
	{
		std::cout << "|";
		for (int j = 0; j < size.first; ++j)
		{
			print_object(field.get_cell_type(std::make_pair(j, i)), field.disabled_object(j, i));
		}
		std::cout << "|" << std::endl;
	}
	print_horizontal_border(size.first + 2);
}

// ����� ������������ ������� �������� ����.
void view::print_object(cell_type type, bool disabled)
{
	switch (type)
	{
		// ����� ������ ������ ����.
	case cell_type::Empty:
		std::cout << " ";
		return;

		// ������ � ����������: ������ "+".
	case cell_type::Artifact:
		std::cout << "\033[32m" << "+";
		break;

		// ������ � ���������: ������� ��� ������� (���� ������� ������) "�".
	case cell_type::Ghost:
		if (disabled)
		{
			std::cout << "\033[36m" << "x";
		}
		else
		{
			std::cout << "\033[31m" << "x";
		}
		break;

		// ������ � ��������: ����� ��� ������� (���� ������� ������������) "#".
	case cell_type::Trap:
		if (disabled)
		{
			std::cout << "\033[36m" << "#";
		}
		else
		{
			std::cout << "\033[90m" << "#";
		}
		break;

		// ������ � �������: ����� "�".
	default:
		std::cout << "\033[33m" << "o";
		break;
	}
	// ������� ������� ����� ��� ������������ ������ � �������.
	std::cout << "\033[0m";
}

// ����� �������� ������ ����.
void view::print_level(int level)
{
    std::cout << "Level " << level << std::endl;
}

// ����� �������� ��������� �������� ������.
void view::print_lives(int current, int total)
{
	std::cout << "Lives: " << current << "/" << total << "." << std::endl;
}

// ����� ����� ��������� ���������� ����� ����.
void view::print_artifacts_collected(int collected, int total)
{
	std::cout << "Collected " << collected << "/" << total << " artifacts." << std::endl;
}

void view::print_ghosts_begin_chase(int amount)
{
	if (amount == 1)
	{
		std::cout << "1 ghost noticed you. He's started chasing!" << std::endl;
	}
	else
	{
		std::cout << amount << " ghosts noticed you. They've started chasing!"
			<< std::endl;
	}
}

void view::print_ghosts_chasing(int amount)
{
	if (amount == 1)
	{
		std::cout << "1 ghost is chasing you." << std::endl;
	}
	else
	{
		std::cout << amount << " ghosts in total are chasing you." << std::endl;
	}
}

void view::print_loses(int amount)
{
	if (amount == 1)
	{
		std::cout << "A ghost has frightened you! You've lost life." << std::endl;
	}
	else
	{
		std::cout << amount << " ghosts have frightened you! You lose "	<< amount << " lives." << std::endl;
	}
}

void view::level_up()
{
	std::cout << "You won! Press any key to go to the next level." << std::endl;
	_getch();
}

bool view::game_over(int level)
{
	std::cout << std::endl << "GAME OVER" << std::endl;
	std::cout << std::endl << "You can replay level " << level << " with 3/5 lives." << std::endl;
	std::cout << "Replay ? [y / n]" << std::endl << std::endl;

	if (_getch() != 'y')
	{
		std::cout << "Press Esc to close." << std::endl;
		return true;
	}
	return false;
}

void view::finish()
{
	std::cout << std::endl << "CONGRATULATIONS! You've passed the game." << std::endl << std::endl;
}

// ��������� ������� ������ �� ������ (1 �������).
int view::get_input()
{
	return _getch();
}

// ����� ��������� �� �������� ���� �� ������.
void view::print_make_turn()
{
	std::cout << "Make your turn!" << std::endl;
}

// ����� ������ ������-�����������.
void view::print_empty_line()
{
	std::cout << std::endl;
}

// ����� �������/������ ������� ���� � ��������� ����� �������.
void view::print_horizontal_border(int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
}

// ������� ������ �������.
void view::clear_console()
{
	system("cls");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}
