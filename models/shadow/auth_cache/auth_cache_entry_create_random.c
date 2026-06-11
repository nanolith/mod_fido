/**
 * \file models/shadow/auth_cache/auth_cache_entry_create_random.c
 *
 * \brief Create a random cache entry.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

dev_t nondet_dev();
uid_t nondet_uid();
sbintime_t nondet_sbintime();

int auth_cache_entry_create_random(auth_cache_entry** entry)
{
    *entry = malloc(sizeof(**entry), M_FIDO, M_WAITOK | M_ZERO);
    if (NULL == *entry)
    {
        return 1;
    }

    (*entry)->key = nondet_dev();
    (*entry)->cached_uid = nondet_uid();
    (*entry)->expire_time = nondet_sbintime();

    return 0;
}
