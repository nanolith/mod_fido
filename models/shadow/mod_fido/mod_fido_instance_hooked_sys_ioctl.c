/**
 * \file models/shadow/mod_fido/mod_fido_instance_hooked_sys_ioctl.c
 *
 * \brief Shadow implementation of \ref mod_fido_instance_hooked_sys_ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

static int nondet_retval();

int
mod_fido_instance_hooked_sys_ioctl(struct thread *td, void *args)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hooked_sys_ioctl, td, args);

    int retval = nondet_retval();
    MODEL_ASSUME(property_error_code_is_expected_for_ioctl_syscall(retval));

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hooked_sys_ioctl, retval, td, args);

    return retval;
}
