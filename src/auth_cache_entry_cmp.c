/**
 * \file auth_cache_entry_cmp.c
 *
 * \brief Compare two auth_cache_entry instances.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "auth_cache.h"

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
auth_cache_entry_cmp(auth_cache_entry *lhs, auth_cache_entry *rhs)
{
    if (lhs->key < rhs->key)
    {
        return -1;
    }
    else if (lhs->key > rhs->key)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
