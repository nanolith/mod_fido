/**
 * \file models/shadow/kernel/mtx_init.c
 *
 * \brief Initialize a mutex object.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int kernel_mtx_valid;

void mtx_init(struct mtx* mtx, const char* name, const char* type, int opts)
{
    MODEL_ASSERT(MTX_DEF == opts);

    int retval = pthread_mutex_init(&mtx->mtx, NULL);
    if (0 != retval)
    {
        /* trim this path. */
        MODEL_ASSUME(0);
    }

    mtx->valid = kernel_mtx_valid;
    mtx->locked = 0;
}
