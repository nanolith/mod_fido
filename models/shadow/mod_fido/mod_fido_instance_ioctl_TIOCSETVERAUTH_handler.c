/**
 * \file models/shadow/mod_fido/mod_fido_instance_ioctl_TIOCSETVERAUTH_handler.c
 *
 * \brief Shadow implementation of
 * \ref mod_fido_instance_ioctl_TIOCSETVERAUTH_handler.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

int
mod_fido_instance_ioctl_TIOCSETVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_TIOCSETVERAUTH_handler, inst, td, args);

    retval = nondet_retval();
    MODEL_ASSUME(property_error_code_is_expected_for_ioctl_syscall(retval));

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_TIOCSETVERAUTH_handler, retval, inst, td, args);

    return retval;
}
