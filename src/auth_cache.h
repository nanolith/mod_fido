/**
 * \file auth_cache.h
 *
 * \brief Data structures and methods for working with the authentication cache.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <mod_fido/model_assert.h>
#include <sys/tree.h>
#include <sys/types.h>

/**
 * \brief An entry in the auth cache.
 */
typedef struct auth_cache_entry auth_cache_entry;
struct auth_cache_entry
{
    dev_t       key;
    uid_t       cached_uid;
    sbintime_t  expire_time;

    RB_ENTRY(auth_cache_entry) link;
};

/**
 * \brief Auth cache table.
 */
RB_HEAD(auth_cache_table, auth_cache_entry);

/**
 * \brief Compare two auth_cache entries.
 *
 * \param lhs           The left-hand side of the comparison.
 * \param rhs           The right-hand side of the comparison.
 *
 * \returns An integer value describing the comparison result:
 *      - a negative value if lhs < rhs.
 *      - a positive value if lhs > rhs.
 *      - zero if lhs == rhs.
 */
int
auth_cache_entry_cmp(auth_cache_entry *lhs, auth_cache_entry *rhs);

/* Red-black tree for the auth cache entries. */
RB_PROTOTYPE(auth_cache_table, auth_cache_entry, link, auth_cache_entry_cmp)
