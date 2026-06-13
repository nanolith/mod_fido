/**
 * \file models/shadow/kernel/ioctl_args_create_random.c
 *
 * \brief Helpers to create and release ioctl_args instances.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();
void* nondet_vptr();

int ioctl_args_create_random(struct ioctl_args** args)
{
    *args =
        (struct ioct_args*)malloc(sizeof(**args), M_FIDO, M_WAITOK | M_ZERO);
    if (NULL == *args)
    {
        return 1;
    }

    (*args)->fd = nondet_int();
    (*args)->data = nondet_vptr();

    return 0;
}

void ioctl_args_release(struct ioctl_args* args)
{
    free(args);
}
