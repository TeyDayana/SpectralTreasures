#include "trap.h"

trap::trap()
{
}

// Получение информации о том, была ли активирована ловушка.
bool trap::is_active()
{
	return active;
}

// Активация ловушки.
void trap::activate()
{
	active = true;
}
