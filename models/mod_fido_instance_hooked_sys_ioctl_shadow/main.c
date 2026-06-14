/**
 * \file models/mod_fido_instance_hooked_sys_ioctl_shadow/main.c
 *
 * \brief Model checks for the shadow implementation of
 * \ref mod_fido_instance_hooked_sys_ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

int main(int argc, char* argv[])
{
    int retval, release_retval;
    struct thread* td;
    struct ioctl_args* args;

    /* create the global instance. */
    retval = mod_fido_instance_create_random(&mod_fido_global_inst);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* force the instance to not be hooked. */
    mod_fido_global_inst->old_sys_ioctl = NULL;

    /* hook the instance. */
    mtx_lock(&mod_fido_global_inst->fido_mtx);
    mod_fido_instance_hook_ioctl_locked(mod_fido_global_inst);
    mtx_unlock(&mod_fido_global_inst->fido_mtx);

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

    /* Call the hooked ioctl handler. */
    retval = mod_fido_instance_hooked_sys_ioctl(td, args);
    if (0 != retval)
    {
        goto done;
    }

    goto done;

done:
    release_retval = mod_fido_instance_release(mod_fido_global_inst);
    if (0 != release_retval)
    {
        retval = release_retval;
    }

    ioctl_args_release(args);
    thread_release(td);

    return retval;
}
