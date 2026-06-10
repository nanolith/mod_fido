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
#include <sys/ioccom.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/module.h>
#include <sys/file.h>
#include <sys/sysproto.h>
#include <sys/sysent.h>
#include <sys/systm.h>
#include <sys/tty.h>

#include <mod_fido/function_contracts.h>
#include <mod_fido/function_decl.h>
#include <mod_fido/model_assert.h>

#include "auth_cache.h"

/* TTY IOCTLs. */
#define TIOCSETVERAUTH    _IOW('t', 200, int)
#define TIOCCHKVERAUTH    _IOR('t', 201, int)
#define TIOCCLRVERAUTH    _IO('t', 202)

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

/**
 * \brief Handle custom TTY TIOCSETVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCSETVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCSETVERAUTH_handler,
    mod_fido_instance* inst, struct thread* td, struct ioctl_args* args)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
        /* args is valid. */
        MODEL_ASSERT(property_ioctl_args_valid(args));
MODEL_CONTRACT_PRECONDITIONS_END(
    mod_fido_instance_ioctl_TIOCSETVERAUTH_handler)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCSETVERAUTH_handler,
    int retval, mod_fido_instance* inst, struct thread* td,
    struct ioctl_args* args)
        /* the return value is one of the expected return values for ioctl. */
        MODEL_ASSERT(property_error_code_is_expected_for_ioctl_syscall(retval));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
MODEL_CONTRACT_POSTCONDITIONS_END(
    mod_fido_instance_ioctl_TIOCSETVERAUTH_handler)

/**
 * \brief Handle custom TTY TIOCCHKVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler,
    mod_fido_instance* inst, struct thread* td, struct ioctl_args* args)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
        /* args is valid. */
        MODEL_ASSERT(property_ioctl_args_valid(args));
MODEL_CONTRACT_PRECONDITIONS_END(
    mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler,
    int retval, mod_fido_instance* inst, struct thread* td,
    struct ioctl_args* args)
        /* the return value is one of the expected return values for ioctl. */
        MODEL_ASSERT(property_error_code_is_expected_for_ioctl_syscall(retval));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
MODEL_CONTRACT_POSTCONDITIONS_END(
    mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler)

/**
 * \brief Handle custom TTY TIOCCLRVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 * \param privcheck     Set to 1 to perform the privilege check, and 0
 *                      otherwise.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args,
    int privcheck);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler,
    mod_fido_instance* inst, struct thread* td, struct ioctl_args* args,
    int privcheck)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
        /* args is valid. */
        MODEL_ASSERT(property_ioctl_args_valid(args));
MODEL_CONTRACT_PRECONDITIONS_END(
    mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler,
    int retval, mod_fido_instance* inst, struct thread* td,
    struct ioctl_args* args, int privcheck)
        /* the return value is one of the expected return values for ioctl. */
        MODEL_ASSERT(property_error_code_is_expected_for_ioctl_syscall(retval));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(inst));
MODEL_CONTRACT_POSTCONDITIONS_END(
    mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler)

/**
 * \brief Try to get the tty pointer from a given set of ioctl args.
 *
 * \note As a side-effect, this method will hook a pseudo-terminal for further
 * processing.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns the tty for this ioctl if found, or NULL if not found.
 */
struct tty*
mod_fido_instance_ioctl_tty_get_locked(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_ioctl_tty_get_locked, mod_fido_instance* inst,
    struct thread* td, struct ioctl_args* args)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
        /* args is valid. */
        MODEL_ASSERT(property_ioctl_args_valid(args));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_ioctl_tty_get_locked)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_ioctl_tty_get_locked, struct tty* retval,
    mod_fido_instance* inst, struct thread* td, struct ioctl_args* args)
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* if the returned tty is not NULL... */
        if (NULL != retval)
        {
            /* it is a valid tty instance. */
            MODEL_ASSERT(property_tty_valid(retval));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_ioctl_tty_get_locked)

/**
 * \brief Hook the file options table for a given file handle.
 *
 * \param inst          The mod_fido instance for this operation.
 * \param fp            The file handle to hook.
 */
void
mod_fido_instance_hook_pts_fops_locked(
    mod_fido_instance* inst, struct file *fp);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_hook_pts_fops_locked, mod_fido_instance* inst,
    struct file* fp)
        /* inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(inst));
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* fp is valid. */
        MODEL_ASSERT(property_file_handle_valid(fp));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_hook_pts_fops_locked)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_hook_pts_fops_locked, mod_fido_instance* inst,
    struct file* fp)
        /* inst is locked. */
        MODEL_ASSERT(property_mod_fido_instance_locked(inst));
        /* old file options preserved. */
        MODEL_ASSERT(NULL != inst->old_pts_fo);
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_hook_pts_fops_locked)

/**
 * \brief Hooked method for closing a file handle.
 *
 * \param fp            The file handle to hook.
 * \param td            The thread for this operation.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_hooked_file_handle_close(
    struct file *fp, struct thread* td);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    mod_fido_instance_hooked_file_handle_close, struct file* fp,
    struct thread* td)
        /* mod_fido_global_inst is valid. */
        MODEL_ASSERT(property_mod_fido_instance_valid(mod_fido_global_inst));
        /* inst is not locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(mod_fido_global_inst));
        /* fp is valid. */
        MODEL_ASSERT(property_file_handle_valid(fp));
        /* td is valid. */
        MODEL_ASSERT(property_kernel_thread_valid(td));
MODEL_CONTRACT_PRECONDITIONS_END(mod_fido_instance_hooked_file_handle_close)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    mod_fido_instance_hooked_file_handle_close, int retval, struct file* fp,
    struct thread* td)
        /* the return value is an expected return value for file close. */
        MODEL_ASSERT(property_error_code_is_expected_for_file_close(retval));
        /* inst is NOT locked. */
        MODEL_ASSERT(!property_mod_fido_instance_locked(mod_fido_global_inst));
MODEL_CONTRACT_POSTCONDITIONS_END(mod_fido_instance_hooked_file_handle_close)
