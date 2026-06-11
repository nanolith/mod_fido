/**
 * \file models/shadow/kernel/property_mtx_valid.c
 *
 * \brief Check if a mutex is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int kernel_mtx_valid;

bool property_mtx_valid(const struct mtx* mutex)
{
    MODEL_ASSERT(mutex->valid == kernel_mtx_valid);

    return true;
}
