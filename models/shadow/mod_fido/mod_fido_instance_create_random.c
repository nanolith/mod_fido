/**
 * \file models/shadow/mod_fido/mod_fido_instance_create_random.c
 *
 * \brief Shadow implementation of \ref mod_fido_instance_create_random.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int mod_fido_instance_create_random(mod_fido_instance** inst)
{
    *inst =
        (mod_fido_instance*)malloc(sizeof(**inst), M_FIDO, M_WAITOK | M_ZERO);
    if (NULL == *inst)
    {
        return 1;
    }
    mtx_init(&(*inst)->fido_mtx, "mod_fido mutex", NULL, MTX_DEF);
    RB_INIT(&(*inst)->auth_cache);
    (*inst)->hooked_count = 0;

    return 0;
}
