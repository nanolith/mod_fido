/**
 * \file models/mod_fido_instance_ioctl_TIOCSETVERAUTH_handler/main.c
 *
 * \brief Model checks for \ref mod_fido_instance_ioctl_TIOCSETVERAUTH_handler.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int main(int argc, char* argv[])
{
    int retval, release_retval;
    mod_fido_instance* inst;
    struct thread* td;
    struct ioctl_args* args;

    /* create an instance. */
    retval = mod_fido_instance_create_random(&inst);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* create a thread. */
    retval = thread_create_random(&td);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* create ioctl args. */
    retval = ioctl_args_create_random(&args);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* Handle a TIOCSETVERAUTH ioctl. */
    retval = mod_fido_instance_ioctl_TIOCSETVERAUTH_handler(inst, td, args);
    if (0 != retval)
    {
        goto done;
    }

    goto done;

done:
    release_retval = mod_fido_instance_release(inst);
    if (0 != release_retval)
    {
        retval = release_retval;
    }

    ioctl_args_release(args);
    thread_release(td);

    return retval;
}
