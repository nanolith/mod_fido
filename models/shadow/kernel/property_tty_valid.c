/**
 * \file models/shadow/kernel/property_tty_valid.c
 *
 * \brief Check if a tty instance is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

bool property_tty_valid(const struct tty* tp)
{
    return NULL != tp;
}
