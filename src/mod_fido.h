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
    sy_call_t *old_sys_ioctl;
    const struct fileops *old_pts_fo;
    struct fileops hooked_pts_fops;
    size_t hooked_count;
    struct auth_cache_table auth_cache;
};

/**
 * \brief The global mod_fido instance defined in mod_fido_inst.c
 */
extern mod_fido_instance* mod_fido_global_inst;

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

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_release, mod_fido_instance* inst)
        /* inst is readable and writable. */
        MODEL_CHECK_OBJECT_RW(inst, sizeof(*inst));
        /* inst->mtx must be valid. */
        MODEL_ASSERT(property_mtx_valid(&inst->fido_mtx));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_release, int retval, mod_fido_instance* inst)
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_release)

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Hook the IOCTL syscall in the sysent table.
 *
 * \note This is a total hack. In a production system, once this is done, it
 * can't be undone, without crashing your machine. For testing, you might be
 * able to undo it without a crazy protection violation. Maybe.
 *
 * This operation must be performed under the fido_mtx lock.
 *
 * \param inst          The instance for this hooking operation.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
void
mod_fido_instance_hook_ioctl_locked(
    mod_fido_instance* inst);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_hook_ioctl_locked, mod_fido_instance* inst)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* inst is not yet hooked. */
        MODEL_ASSERT(!property_mod_fido_instance_hooked(inst));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_hook_ioctl_locked)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_hook_ioctl_locked, mod_fido_instance* inst)
        /* inst is hooked. */
        MODEL_ASSERT(property_mod_fido_instance_hooked(inst));
        /* inst is still locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_hook_ioctl_locked)

/**
 * \brief Unhook the IOCTL syscall in the sysent table.
 *
 * \note This undoes the hack above. In an SMP system, this does NOT guarantee
 * that a different kernel thread may still have this entry cached. This is
 * useful when attempting to unload a debug module, but should be avoided in
 * production. Use at your own risk.
 *
 * This operation must be performed under the fido_mtx lock.
 *
 * \param inst          The instance for this hooking operation.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
void
mod_fido_instance_unhook_ioctl_locked(
    mod_fido_instance* inst);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_unhook_ioctl_locked, mod_fido_instance* inst)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* inst is hooked. */
        MODEL_ASSERT(property_mod_fido_instance_hooked(inst));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_unhook_ioctl_locked)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_unhook_ioctl_locked, mod_fido_instance* inst)
        /* inst is not hooked. */
        MODEL_ASSERT(!property_mod_fido_instance_hooked(inst));
        /* inst is still locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_unhook_ioctl_locked)

/**
 * \brief IOCTL hook for mod_fido.
 *
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_hooked_sys_ioctl(struct thread *td, void *args);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_hooked_sys_ioctl, struct thread* td, void* args)
        /* mod_fido_global_inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(mod_fido_global_inst));
        /* mod_fido_global_inst is hooked. */
        MODEL_ASSERT(property_mod_fido_instance_hooked(mod_fido_global_inst));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(mod_fido_global_inst));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
        /* args is valid. */
        MODEL_ASSERT(property_ioctl_args_valid((struct ioctl_args*)args));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_hooked_sys_ioctl)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_hooked_sys_ioctl, int retval, struct thread* td,
    void* args)
        /* the return value is one of the expected return values for ioctl. */
        MODEL_ASSERT(property_error_code_is_expected_for_ioctl_syscall(retval));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(mod_fido_global_inst));
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_hooked_sys_ioctl)
