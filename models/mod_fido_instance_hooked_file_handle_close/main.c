/**
 * \file models/mod_fido_instance_hooked_file_handle_close/main.c
 *
 * \brief Model checks for \ref mod_fido_instance_hooked_file_handle_close.
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
    struct file* fp;
    cap_rights_t rights;

    /* create the global instance. */
    retval = mod_fido_instance_create_random(&mod_fido_global_inst);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* make this the last hooked file handle. */
    mod_fido_global_inst->hooked_count = 1;

    /* create a thread. */
    retval = thread_create_random(&td);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* create the fp. */
    retval = fget(td, nondet_int(), &rights, &fp);
    if (0 != retval)
    {
        MODEL_ASSUME(0);
    }

    /* force the old pts to NULL so we can "hook" it. */
    mod_fido_global_inst->old_pts_fo = NULL;

    /* hook the pts. */
    mtx_lock(&mod_fido_global_inst->fido_mtx);
    mod_fido_instance_hook_pts_fops_locked(mod_fido_global_inst, fp);
    mtx_unlock(&mod_fido_global_inst->fido_mtx);

    /* Call the hooked file handle close handler. */
    retval = mod_fido_instance_hooked_file_handle_close(fp, td);
    if (0 != retval)
    {
        goto done;
    }

    goto done;

done:
    /* force the hooked count to 0 to clean up this instance. */
    mod_fido_global_inst->hooked_count = 0;

    release_retval = mod_fido_instance_release(mod_fido_global_inst);
    if (0 != release_retval)
    {
        retval = release_retval;
    }

    fdrop(fp, td);
    thread_release(td);

    return retval;
}
