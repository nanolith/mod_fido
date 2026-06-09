/**
 * \file mod_fido_instance_hook_ioctl_locked.c
 *
 * \brief Hook the syscall table for ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/syscall.h>
#include <sys/sysproto.h>

#include "mod_fido.h"

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
    mod_fido_instance* inst)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);

    /* cache the old IOCTL syscall handler. */
    inst->old_sys_ioctl = sysent[SYS_ioctl].sy_call;

    /* patch in the new handler. */
    sysent[SYS_ioctl].sy_call = &mod_fido_instance_hooked_sys_ioctl;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);
}
