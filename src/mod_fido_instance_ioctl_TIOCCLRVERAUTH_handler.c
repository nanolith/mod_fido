/**
 * \file mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler.c
 *
 * \brief Handler for the TIOCCLRVERAUTH ioctl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Handle custom TTY TIOCCLRVERAUTH IOCTL.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 * \param privcheck     Set to 1 to perform the privilege check, and 0
 *                      otherwise.
 *
 * \returns a error code. 0 on success and an error number on failure.
 */
int
mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args,
    int privcheck)
{
    int retval;
    struct tty* tp;
    auth_cache_entry find_entry;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler, inst, td, args,
        privcheck);

    /* try to get the tty pointer. */
    tp = mod_fido_instance_ioctl_tty_get(inst, td, args);
    if (NULL == tp)
    {
        retval = ENOTTY;
        goto done;
    }

    /* perform a privilege check. */
    if (privcheck)
    {
        retval = priv_check(td, PRIV_DRIVER);
        if (0 != retval)
        {
            retval = EPERM;
            goto done;
        }
    }

    /* pre-calculate data. */
    find_entry.key = tty_udev(tp);

    /* look up entry. */
    mtx_lock(&inst->fido_mtx);
    auth_cache_entry* entry =
        RB_FIND(auth_cache_table, &inst->auth_cache, &find_entry);
    if (NULL == entry)
    {
        mtx_unlock(&inst->fido_mtx);
        retval = 0;
        goto done;
    }

    /* Remove the entry to clear the credentials. */
    RB_REMOVE(auth_cache_table, &inst->auth_cache, entry);
    mtx_unlock(&inst->fido_mtx);
    free(entry, M_FIDO);

    /* success. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_TIOCCLRVERAUTH_handler, retval, inst, td, args,
        privcheck);

    return retval;
}
