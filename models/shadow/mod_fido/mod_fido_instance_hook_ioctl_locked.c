/**
 * \file models/shadow/mod_fido/mod_fido_instance_hook_ioctl_locked.c
 *
 * \brief Shadow implementation of \ref mod_fido_instance_hook_ioctl_locked.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

void
mod_fido_instance_hook_ioctl_locked(
    mod_fido_instance* inst)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);

    inst->old_sys_ioctl = &mod_fido_instance_hooked_sys_ioctl;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hook_ioctl_locked, inst);
}
