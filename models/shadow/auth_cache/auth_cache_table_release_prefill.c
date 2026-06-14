/**
 * \file models/shadow/auth_cache/auth_cache_table_release_prefill.c
 *
 * \brief Release a pre-filled entry provided by \ref auth_cache_table_init.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

extern auth_cache_entry* auth_cache_table_prefill_entry;
extern int auth_cache_table_prefill_entry_exists;

void auth_cache_table_release(void)
{
    if (auth_cache_table_prefill_entry_exists)
    {
        free(auth_cache_table_prefill_entry, M_FIDO);
        auth_cache_table_prefill_entry_exists = 0;
    }
}
