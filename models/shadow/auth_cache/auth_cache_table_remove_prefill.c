/**
 * \file models/shadow/auth_cache/auth_cache_table_remove_prefill.c
 *
 * \brief "Remove" an entry from the auth cache table. If this entry is our
 * prefill entry, then set the prefill entry to NULL.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

extern auth_cache_entry* auth_cache_table_prefill_entry;
extern int auth_cache_table_prefill_entry_exists;

auth_cache_entry* auth_cache_table_remove(auth_cache_entry* root, auth_cache_entry* entry)
{
    if (auth_cache_table_prefill_entry == entry)
    {
        auth_cache_table_prefill_entry = NULL;
        auth_cache_table_prefill_entry_exists = false;
    }

    return NULL;
}
