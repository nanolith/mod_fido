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
#include <sys/file.h>
#include <sys/sysent.h>

#include <mod_fido/function_contracts.h>
#include <mod_fido/function_decl.h>
#include <mod_fido/model_assert.h>

#include "auth_cache.h"

/**
 * \brief The fido kernel module instance.
 */
typedef struct mod_fido_instance mod_fido_instance;
struct mod_fido_instance
{
    struct mtx doas_mtx;
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
