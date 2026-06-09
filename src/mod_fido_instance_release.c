/**
 * \file mod_fido_instance_release.c
 *
 * \brief Release a mod_fido instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/mutex.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>

#include "mod_fido.h"

/**
 * \brief Release a \ref mod_fido_instance.
 *
 * \note Release will fail if the hooked count is greater than zero; the
 * instance cannot be released until all hooked terminals and pseudoterminals
 * have been closed.
 *
 * \param inst          The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
mod_fido_instance_release(
    mod_fido_instance* inst)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(mod_fido_instance_release, inst);

    /* lock the mutex before continuing. */
    mtx_lock(&inst->fido_mtx);

    /* To release this instance, the hooked count must be zero. */
    if (inst->hooked_count > 0)
    {
        mtx_unlock(&inst->fido_mtx);
        retval = 1;
        goto done;
    }

    /* disable the hook if it has been enabled. */
    if (NULL != inst->old_sys_ioctl)
    {
        mod_fido_instance_unhook_ioctl_locked(inst);
    }

    /* release all entries in our auth cache table. */
    struct auth_cache_entry* entry;
    struct auth_cache_entry* tmp;
    RB_FOREACH_SAFE(entry, auth_cache_table, &inst->auth_cache, tmp) {
        RB_REMOVE(auth_cache_table, &inst->auth_cache, entry);
        free(entry, M_FIDO);
    }

    /* unlock the mutex. */
    mtx_unlock(&inst->fido_mtx);

    /* destroy the mutex. */
    mtx_destroy(&inst->fido_mtx);

    /* success. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_release, retval, inst);

    return retval;
}
