/**
 * \file models/shadow/kernel/copyin.c
 *
 * \brief Shadow implementation of \ref copyin.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

int copyin(const void *uaddr, void *kaddr, size_t len)
{
    MODEL_CHECK_OBJECT_RW(kaddr, len);

    int retval = nondet_int();

    if (0 == retval)
    {
        __CPROVER_havoc_slice(kaddr, len);
    }

    return retval;
}
