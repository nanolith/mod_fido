/**
 * \file mod_fido.h
 *
 * \brief The fido kernel module instance and helper routines.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/file.h>
#include <sys/sysent.h>

#include <mod_fido/function_contracts.h>
#include <mod_fido/function_decl.h>
#include <mod_fido/model_assert.h>

#include "auth_cache.h"

/**
 * \brief The arena for the fido module.
 */
MALLOC_DECLARE(M_FIDO);

/**
 * \brief The fido kernel module instance.
 */
typedef struct mod_fido_instance mod_fido_instance;
struct mod_fido_instance
{
    struct mtx fido_mtx;
    int fido_mtx_initialized;
    sy_call_t *old_sys_ioctl;
    const struct fileops *old_pts_fo;
    struct fileops hooked_pts_fops;
    size_t hooked_count;
    struct auth_cache_table auth_cache;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid \ref mod_fido_instance.
 *
 * \param inst          The instance to check.
 *
 * \returns 1 if the instance is valid and 0 otherwise.
 */
int
property_mod_fido_instance_valid(
    const mod_fido_instance* inst);

/**
 * \brief The \ref mod_fido_instance has been hooked.
 *
 * \param inst          The instance to check.
 *
 * \returns 1 if the instance is hooked and 0 otherwise.
 */
int
property_mod_fido_instance_hooked(
    const mod_fido_instance* inst);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

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
    mod_fido_instance** inst);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_create, mod_fido_instance** inst)
        /* inst is readable and writable. */
        MODEL_CHECK_OBJECT_RW(inst, sizeof(*inst));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_create, int retval, mod_fido_instance** inst)
        /* on success... */
        if (0 == retval)
        {
            /* *inst is a valid instance. */
            MODEL_ASSERT(property_mod_fido_instance_valid(*inst));
        }
        else
        {
            /* *inst is NULL. */
            MODEL_ASSERT(NULL == (*inst));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_create)

/**
 * \brief Release a \ref mod_fido_instance.
 *
 * \note Release will fail if the hooked count is greater than zero; the
 * instance cannot be released until all hooked terminals and pseudoterminals
 * have been closed.
 *
 * \param inst          The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
mod_fido_instance_release(
    mod_fido_instance* inst);
