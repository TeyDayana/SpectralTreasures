#include "player.h"

// »нкапсул€ци€: получение приватной переменной - уровн€ игрока.
int player::get_level()
{
    return level;
}

// ѕолучение текущего состо€ни€ здоровь€ (количества жизней).
int player::get_health()
{
    return health;
}

// ѕолучение максимального количества жизней.
int player::get_max_health()
{
    return max_health;
}

// ѕроверка: жив ли игрок (остались жизни).
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
