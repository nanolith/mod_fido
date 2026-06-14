/**
 * \file models/shadow/auth_cache/auth_cache_table_insert_sink.c
 *
 * \brief Shadow method for RB_INSERT over the auth_cache_table; this
 * implementation is a sink that frees the entry.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

auth_cache_entry* auth_cache_table_insert(
    auth_cache_entry* root, auth_cache_entry* entry)
{
    free(entry, M_FIDO);

    return NULL;
}
