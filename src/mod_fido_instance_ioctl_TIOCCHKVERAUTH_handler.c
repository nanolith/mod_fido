/**
 * \file mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler.c
 *
 * \brief Handler for the TIOCCHKVERAUTH ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Handle custom TTY TIOCCHKVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args)
{
    int retval;
    struct tty* tp;
    auth_cache_entry find_entry;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler, inst, td, args);

    /* try to get the tty pointer. */
    tp = mod_fido_instance_ioctl_tty_get(inst, td, args);
    if (NULL == tp)
    {
        retval = ENOTTY;
        goto done;
    }

    /* perform a privilege check. */
    retval = priv_check(td, PRIV_DRIVER);
    if (0 != retval)
    {
        goto done;
    }

    /* get the current uptime. */
    int current_secs = (int)(getsbinuptime() >> 32);

    /* pre-calculate data. */
    dev_t tty_key = tty_udev(tp);
    uid_t caller_id = td->td_ucred->cr_ruid;
    find_entry.key = tty_key;

    /* look up entry. */
    mtx_lock(&inst->fido_mtx);
    auth_cache_entry* entry =
        RB_FIND(auth_cache_table, &inst->auth_cache, &find_entry);
    if (NULL == entry)
    {
        mtx_unlock(&inst->fido_mtx);
        retval = ENOENT;
        goto done;
    }

    /* is this entry valid, and current? */
    if (entry->cached_uid == caller_id && current_secs < entry->expire_time)
    {
        mtx_unlock(&inst->fido_mtx);
        retval = 0;
        goto done;
    }

    /* remove for any other circumstance (e.g. uid mismatch or expired). */
    RB_REMOVE(auth_cache_table, &inst->auth_cache, entry);
    mtx_unlock(&inst->fido_mtx);
    free(entry, M_FIDO);

    /* valid credentials not found. */
    retval = ENOENT;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_TIOCCHKVERAUTH_handler, retval, inst, td, args);

    return retval;
}
