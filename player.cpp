#include "player.h"

// ������������: ��������� ��������� ���������� - ������ ������.
int player::get_level()
{
    return level;
}

// ��������� �������� ��������� �������� (���������� ������).
int player::get_health()
{
    return health;
}

// ��������� ������������� ���������� ������.
int player::get_max_health()
{
    return max_health;
}

// ��������: ��� �� ����� (�������� �����).
bool player::is_alive()
{
    return health > 0;
}

void player::get_bitten(int amount)
{
    if (amount >= health)
    {
        health = 0;
    }
    else
    {
        health -= amount;
    }
}

int player::level_up()
{
    if (health < max_health)
    {
        ++health;
    }
    return ++level;
}

void player::rebirth()
{
    health = max_health / 2 + 1;
}
