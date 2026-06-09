/**
 * \file mod_fido_instance_hooked_file_handle_close.c
 *
 * \brief Hook file handle close.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/tty.h>

#include "mod_fido.h"

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
    struct file *fp, struct thread* td)
{
    int retval;
    auth_cache_entry find_entry;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hooked_file_handle_close, fp, td);

    if (NULL != fp)
    {
        struct tty* tp = fp->f_data;

        if (NULL != tp)
        {
            dev_t tty_key = tty_udev(tp);
            find_entry.key = tty_key;

            mtx_lock(&mod_fido_global_inst->fido_mtx);
            auth_cache_entry* entry =
                RB_FIND(
                    auth_cache_table, &mod_fido_global_inst->auth_cache,
                    &find_entry);
            if (NULL != entry)
            {
                RB_REMOVE(
                    auth_cache_table, &mod_fido_global_inst->auth_cache, entry);
                --(mod_fido_global_inst->hooked_count);
                mtx_unlock(&mod_fido_global_inst->fido_mtx);
                free(entry, M_FIDO);
            }
            else
            {
                --(mod_fido_global_inst->hooked_count);
                mtx_unlock(&mod_fido_global_inst->fido_mtx);
            }
        }
    }

    /* call the original global close handler. */
    retval = mod_fido_global_inst->old_pts_fo->fo_close(fp, td);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hooked_file_handle_close, retval, fp, td);

    return retval;
}
