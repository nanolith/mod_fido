/**
 * \file models/shadow/auth_cache/auth_cache_table_find.c
 *
 * \brief Shadow method for RB_FIND over the auth_cache_table, acting as a
 * source of entries.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

auth_cache_entry* auth_cache_table_find(
    auth_cache_entry* root, auth_cache_entry* key)
{
    auth_cache_entry* entry;
    int retval = nondet_retval();

    if (0 == retval)
    {
        retval = auth_cache_entry_create_random(&entry);
        if (0 != retval)
        {
            /* trim branch. */
            MODEL_ASSUME(0);
        }

        return entry;
    }

    return NULL;
}
