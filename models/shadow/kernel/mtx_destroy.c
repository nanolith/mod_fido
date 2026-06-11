/**
 * \file models/shadow/kernel/mtx_destroy.c
 *
 * \brief Destroy a mutex object.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

void mtx_destroy(struct mtx* mtx)
{
    MODEL_ASSERT(property_mtx_valid(mtx));

    int retval = pthread_mutex_destroy(&mtx->mtx);
    if (0 != retval)
    {
        /* trim this path. */
        MODEL_ASSUME(0);
    }

    mtx->valid = nondet_int();
    MODEL_ASSUME(kernel_mtx_valid != mtx->valid);
}
