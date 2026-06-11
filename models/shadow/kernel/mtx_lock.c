/**
 * \file models/shadow/kernel/mtx_lock.c
 *
 * \brief Lock a mutex object.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

void mtx_lock(struct mtx* mtx)
{
    MODEL_ASSERT(property_mtx_valid(mtx));

    int retval = pthread_mutex_lock(&mtx->mtx);
    if (0 != retval)
    {
        /* trim this path. */
        MODEL_ASSUME(0);
    }

    MODEL_ASSERT(0 == mtx->locked);
    mtx->locked = 1;
}
