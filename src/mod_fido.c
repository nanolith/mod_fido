/**
 * \file mod_fido.c
 *
 * \brief Entry point for the FreeBSD fido kernel module.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int
mod_fido_handler(module_t mod, int type, void *arg)
{
    int error = 0;

    switch (type)
    {
        case MOD_LOAD:
            error = mod_fido_instance_create(&mod_fido_global_inst);
            if (0 != error)
            {
                return error;
            }
            mtx_lock(&mod_fido_global_inst->fido_mtx);
            mod_fido_instance_hook_ioctl_locked(mod_fido_global_inst);
            mtx_unlock(&mod_fido_global_inst->fido_mtx);
            error = 0;
            break;

        case MOD_UNLOAD:
            #ifdef DEBUG
            error = mod_fido_instance_release(mod_fido_global_inst);
            #else
            error = EOPNOTSUPP;
            #endif
            break;

        default:
            error = EOPNOTSUPP;
            break;
    }

    return (error);
}

static moduledata_t fido_mod = {
    "mod_fido",
    mod_fido_handler,
    NULL
};

DECLARE_MODULE(mod_fido, fido_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
