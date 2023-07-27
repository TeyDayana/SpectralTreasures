#include "artifact.h"

artifact::artifact()
{
}

bool artifact::is_valid()
{
    return valid;
}

// —бор артефакта: пометка собранным.
void artifact::collect()
{
    valid = false;
}
