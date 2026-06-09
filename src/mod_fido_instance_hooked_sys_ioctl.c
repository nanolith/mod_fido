/**
 * \file mod_fido_instance_hooked_sys_ioctl.c
 *
 * \brief Hook for the ioctl syscall.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/ttycom.h>

#include "mod_fido.h"

/**
 * \brief IOCTL hook for mod_fido.
 *
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_hooked_sys_ioctl(struct thread *td, void *args)
{
    int retval;
    struct ioctl_args* uap = (struct ioctl_args*)args;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hooked_sys_ioctl, td, args);

    switch (uap->com)
    {
        case TIOCSCTTY:
            retval = mod_fido_global_inst->old_sys_ioctl(td, args);
            if (0 == retval)
            {
                int error =
                    mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler(
                        mod_fido_global_inst, td, uap, 0);
                (void)error;
            }
            break;

        case TIOCSETVERAUTH:
            retval =
                mod_fido_instance_ioctl_TIOCSETVERAUTH_handler(
                    mod_fido_global_inst, td, uap);
            break;

        case TIOCCHKVERAUTH:
            retval =
                mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler(
                    mod_fido_global_inst, td, uap);
            break;

        case TIOCCLRVERAUTH:
            retval =
                mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler(
                    mod_fido_global_inst, td, uap, 1);
            break;

        default:
            retval = mod_fido_global_inst->old_sys_ioctl(td, args);
            break;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hooked_sys_ioctl, retval, td, args);

    return retval;
}
