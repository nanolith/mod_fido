/**
 * \file models/shadow/auth_cache/auth_cache_table_init_prefill.c
 *
 * \brief Initialize a pre-filled auth cache table.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

auth_cache_entry* auth_cache_table_prefill_entry;
int auth_cache_table_prefill_entry_exists = 0;

void auth_cache_table_init(void)
{
    int retval =
        auth_cache_entry_create_random(&auth_cache_table_prefill_entry);
    if (0 != retval)
    {
        /* trim this branch. */
        MODEL_ASSUME(0);
    }

    auth_cache_table_prefill_entry_exists = 1;
}
