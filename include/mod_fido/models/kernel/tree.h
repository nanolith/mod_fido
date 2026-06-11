/**
 * \file models/kernel/tree.h
 *
 * \brief Simplified rbtree declarations for model checking.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stdint.h>
#include <sys/types.h>

#define RB_ENTRY(type) \
struct { \
    struct type *rbe_link[3]; \
}

#define RB_HEAD(name, type) \
struct name { \
    struct type *rbh_root; \
}

#define RB_PROTOTYPE(name, type, y, z) \
type* name##_start(type*); \
type* name##_next(type*); \
type* name##_remove(type*, type*);

#define RB_START(name,root) name##_start(root)

#define RB_NEXT(name,entry) name##_next(entry)
