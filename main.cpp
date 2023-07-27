#include "game.h"

int main()
{
    game game;
    do
    {
        game.generate_field();
        game.print();

        while (true)
        {
            if (!game.player_turn())
            {
                return 0;
            }
            game.ghost_turns();
            game.player_take_damage();

            game.print();
            game.print_warnings();

            if (game.goals_achieved())
            {
                game.level_up();
                break;
            }

            if (game.is_game_over())
            {
                if (game.game_over())
                {
                    return 0;
                }
                break;
            }
        }
    } while (!game.is_finished() && !game.is_game_over());
    game.finish();
    return 0;
}