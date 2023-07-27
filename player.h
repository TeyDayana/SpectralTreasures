#pragma once
class player
{
    // Стартовые показатели игрока в игре.
private:
    int level = 1;
    int health = 5;
    int max_health = 5;

public:
    int get_level();
    int get_health();
    int get_max_health();

    bool is_alive();
    void get_bitten(int amount);
    int level_up();
    void rebirth();
};
