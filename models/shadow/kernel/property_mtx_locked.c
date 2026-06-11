/**
 * \file models/shadow/kernel/property_mtx_locked.c
 *
 * \brief Check if a mutex is locked.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int kernel_mtx_valid;

bool property_mtx_locked(const struct mtx* mutex)
{
    MODEL_ASSERT(property_mtx_valid(mutex));

    return 1 == mutex->locked;
}
