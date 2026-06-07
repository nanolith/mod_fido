/**
 * \file auth_cache_table.c
 *
 * \brief rb-tree implementation for the auth cache table.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <sys/param.h>

#include "auth_cache.h"

RB_GENERATE(auth_cache_table, auth_cache_entry, link, auth_cache_entry_cmp)
