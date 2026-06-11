/**
 * \file models/shadow/auth_cache/auth_cache_table_start_simple_loop.c
 *
 * \brief Start iteration over the auth_cache using a simple loop of 0 to 2
 * entries.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

int auth_cache_table_count;

auth_cache_entry* auth_cache_table_start(auth_cache_entry* root)
{
    auth_cache_entry* entry;
    auth_cache_table_count = nondet_int();
    MODEL_ASSUME(auth_cache_table_count >=0 && auth_cache_table_count <= 2);

    if (auth_cache_table_count > 0)
    {
        --auth_cache_table_count;

        int retval = auth_cache_entry_create_random(&entry);
        if (0 != retval)
        {
            /* trim this branch. */
            MODEL_ASSUME(0);
        }

        return entry;
    }
    else
    {
        return NULL;
    }
}
