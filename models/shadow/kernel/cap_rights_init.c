/**
 * \file models/shadow/kernel/cap_rights_init.c
 *
 * \brief Shadow method to initialize a \ref cap_rights_t structure.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

cap_rights_t* cap_rights_init(cap_rights_t* rights, int capability)
{
    rights->caps = capability;

    return rights;
}
