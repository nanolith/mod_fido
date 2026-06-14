/**
 * \file models/shadow/auth_cache/auth_cache_table_find.c
 *
 * \brief Shadow method for RB_FIND over the auth_cache_table.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

static auth_cache_entry dummy_entry;

auth_cache_entry* auth_cache_table_find(
    auth_cache_entry* root, auth_cache_entry* key)
{
    int retval = nondet_retval();

    if (0 == retval)
    {
        __CPROVER_havoc_object(&dummy_entry);
        return &dummy_entry;
    }

    return NULL;
}
