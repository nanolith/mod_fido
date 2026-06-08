/**
 * \file mod_fido.c
 *
 * \brief Entry point for the FreeBSD fido kernel module.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>

#include "mod_fido.h"

static int
mod_fido_handler(module_t mod, int type, void *arg)
{
    int error = 0;

    switch (type)
    {
        case MOD_LOAD:
            break;

        case MOD_UNLOAD:
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
