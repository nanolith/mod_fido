/**
 * \file mod_fido_instance_hook_pts_fops_locked.c
 *
 * \brief Hook a file handle's file options structure to override close.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Hook the file options table for a given file handle.
 *
 * \param inst          The mod_fido instance for this operation.
 * \param fp            The file handle to hook.
 */
void
mod_fido_instance_hook_pts_fops_locked(
    mod_fido_instance* inst, struct file *fp)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hook_pts_fops_locked, inst, fp);

    if (NULL == fp || NULL == fp->f_ops)
        goto done;

    /* clone the global PTS table if it hasn't previously been cloned. */
    if (NULL == inst->old_pts_fo)
    {
        inst->old_pts_fo = fp->f_ops;

        memcpy(&inst->hooked_pts_fops, fp->f_ops, sizeof(struct fileops));

        /* hook in our close override. */
        inst->hooked_pts_fops.fo_close =
            &mod_fido_instance_hooked_file_handle_close;
    }

    if (&inst->hooked_pts_fops != fp->f_ops)
    {
        ++(inst->hooked_count);
        fp->f_ops = &inst->hooked_pts_fops;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hook_pts_fops_locked, inst, fp);
}
