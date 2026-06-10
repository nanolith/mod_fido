/**
 * \file mod_fido_instance_unhook_ioctl_locked.c
 *
 * \brief Unhook the syscall table for ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

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
    mod_fido_instance* inst)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);

    /* restore the old IOCTL syscall handler. */
    sysent[SYS_ioctl].sy_call = inst->old_sys_ioctl;

    /* set the old handler to NULL to reset the hooked invariant. */
    inst->old_sys_ioctl = NULL;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);
}
