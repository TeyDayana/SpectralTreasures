#include "artifact.h"

artifact::artifact()
{
}

bool artifact::is_valid()
{
    return valid;
}

// ���� ���������: ������� ���������.
void artifact::collect()
{
    valid = false;
}
