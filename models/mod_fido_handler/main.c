/**
 * \file models/mod_fido_handler/main.c
 *
 * \brief Model checks for \ref mod_fido_handler.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

static int nondet_int();
static module_t nondet_mod();
static void* nondet_arg();

int main(int argc, char* argv[])
{
    int retval;

    int type = nondet_int();

    /* force the global instance to NULL. */
    mod_fido_global_inst = NULL;

    /* on MOD_UNLOAD... */
    #ifdef DEBUG
    if (MOD_UNLOAD == type)
    {
        retval = mod_fido_instance_create(&mod_fido_global_inst);
        MODEL_ASSUME(0 == retval);
    }
    #endif

    /* call the handler. */
    retval = mod_fido_handler(nondet_mod(), type, nondet_arg());
    if (0 != retval)
    {
        goto done;
    }

    /* on MOD_LOAD... */
    if (MOD_LOAD == type)
    {
        /* release the instance. */
        retval = mod_fido_instance_release(mod_fido_global_inst);
        if (0 != retval)
        {
            goto done;
        }
    }

done:
    return retval;
}
