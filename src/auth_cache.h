/**
 * \file auth_cache.h
 *
 * \brief Data structures and methods for working with the authentication cache.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

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
