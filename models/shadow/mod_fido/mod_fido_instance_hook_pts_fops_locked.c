/**
 * \file models/shadow/mod_fido/mod_fido_instance_hook_pts_fops_locked.c
 *
 * \brief Shadow implementation of \ref mod_fido_instance_hook_pts_fops_locked.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

void
mod_fido_instance_hook_pts_fops_locked(
    mod_fido_instance* inst, struct file *fp)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_hook_pts_fops_locked, inst, fp);

    inst->old_pts_fo = &mod_fido_instance_hooked_file_handle_close;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_hook_pts_fops_locked, inst, fp);
}
