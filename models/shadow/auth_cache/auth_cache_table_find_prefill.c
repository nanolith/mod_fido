/**
 * \file models/shadow/auth_cache/auth_cache_table_find_prefill.c
 *
 * \brief Shadow method for RB_FIND over the auth_cache_table, using a
 * pre-filled entry provided by \ref auth_cache_table_init.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

extern auth_cache_entry* auth_cache_table_prefill_entry;
extern int auth_cache_table_prefill_entry_exists;

auth_cache_entry* auth_cache_table_find(
    auth_cache_entry* root, auth_cache_entry* key)
{
    int retval = nondet_retval();

    if (0 == retval && auth_cache_table_prefill_entry_exists)
    {
        return auth_cache_table_prefill_entry;
    }

    return NULL;
}
