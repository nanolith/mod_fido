/**
 * \file mod_fido_instance_create.c
 *
 * \brief Create a mod_fido instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/mutex.h>

#include "mod_fido.h"

/**
 * \brief Create a \ref mod_fido_instance.
 *
 * \param inst          Pointer to the instance pointer to set with this
 *                      instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
mod_fido_instance_create(
    mod_fido_instance** inst)
{
    int retval;
    mod_fido_instance* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(mod_fido_instance_create, inst);

    /* allocate memory for this instance. */
    tmp = (mod_fido_instance*)malloc(sizeof(*tmp), M_FIDO, M_WAITOK | M_ZERO);

    /* initialize mutex. */
    mtx_init(&tmp->fido_mtx, "mod_fido mutex", NULL, MTX_DEF);

    /* initialize auth cache table. */
    RB_INIT(&tmp->auth_cache);

    /* success. */
    retval = 0;
    *inst = tmp;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(mod_fido_instance_create, retval, inst);

    return retval;
}
