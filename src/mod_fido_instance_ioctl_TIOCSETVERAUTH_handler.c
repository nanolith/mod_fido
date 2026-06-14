/**
 * \file mod_fido_instance_ioctl_TIOCSETVERAUTH_handler.c
 *
 * \brief Handler for the TIOCSETVERAUTH ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Handle custom TTY TIOCSETVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCSETVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args)
{
    int retval;
    struct tty* tp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_TIOCSETVERAUTH_handler, inst, td, args);

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

    /* extract the timeout duration. */
    int timeout_duration;
    retval = copyin(args->data, &timeout_duration, sizeof(timeout_duration));
    if (0 != retval)
    {
        goto done;
    }

    /* set an bounds for timeout duration. */
    if (timeout_duration < 0 || timeout_duration > 1500)
    {
        retval = EINVAL;
        goto done;
    }

    /* pre-calculate data. */
    dev_t tty_key = tty_udev(tp);
    uid_t caller_id = td->td_ucred->cr_ruid;
    int expiry = current_secs + timeout_duration;

    /* build a cache entry in anticipation of insertion. */
    auth_cache_entry* new_entry =
        malloc(sizeof(auth_cache_entry), M_FIDO, M_WAITOK | M_ZERO);
    new_entry->key = tty_key;
    new_entry->cached_uid = caller_id;
    new_entry->expire_time = expiry;

    /* does this entry already exist? */
    mtx_lock(&inst->fido_mtx);
    auth_cache_entry* entry =
        RB_FIND(auth_cache_table, &inst->auth_cache, new_entry);
    if (NULL != entry)
    {
        entry->cached_uid = caller_id;
        entry->expire_time = expiry;
        mtx_unlock(&inst->fido_mtx);
        free(new_entry, M_FIDO);
    }
    else
    {
        RB_INSERT(auth_cache_table, &inst->auth_cache, new_entry);
        mtx_unlock(&inst->fido_mtx);
    }

    /* success. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_TIOCSETVERAUTH_handler, retval, inst, td, args);

    return retval;
}
