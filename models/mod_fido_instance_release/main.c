/**
 * \file models/mod_fido_instance_release/main.c
 *
 * \brief Model checks for \ref mod_fido_instance_release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

static int mod_fido_instance_create_random(mod_fido_instance** inst)
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

int main(int argc, char* argv[])
{
    int retval;
    auth_cache_entry lhs, rhs;
    mod_fido_instance* inst;

    /* create an instance. */
    retval = mod_fido_instance_create_random(&inst);
    if (0 != retval)
    {
        /* trim this path. */
        MODEL_ASSUME(0);
    }

    /* release the instance. */
    retval = mod_fido_instance_release(inst);
    if (0 != retval)
    {
        goto done;
    }

done:
    return retval;
}
