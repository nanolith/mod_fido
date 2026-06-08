/**
 * \file models/shadow/mod_fido/property_mod_fido_auth_cache_entry_valid.c
 *
 * \brief Verify that an auth cache entry is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "auth_cache.h"

/**
 * \brief Valid auth cache entry property.
 *
 * \param entry         The entry to check.
 *
 * \returns true if the entry is valid.
 */
int
property_mod_fido_auth_cache_entry_valid(
    const auth_cache_entry* entry)
{
    MODEL_CHECK_OBJECT_READ(entry, sizeof(*entry));

    return 1;
}
