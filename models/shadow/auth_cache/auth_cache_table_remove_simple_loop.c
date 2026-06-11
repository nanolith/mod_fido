/**
 * \file models/shadow/auth_cache/auth_cache_table_remove_simple_loop.c
 *
 * \brief "Remove" an entry from the auth cache table. This is a "no op" in the
 * simple loop shadow.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

auth_cache_entry* auth_cache_table_remove(auth_cache_entry* root)
{
    return NULL;
}
