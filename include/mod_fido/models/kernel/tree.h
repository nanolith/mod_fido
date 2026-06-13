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

#define RB_FOREACH_SAFE(i, name, root, x) \
    for (i = RB_START(name, root); NULL != i; i = RB_NEXT(name, i))

#define RB_REMOVE(name, root, entry) \
    name##_remove(root, entry)

#define RB_INIT(root) (root)->rbh_root = NULL

#define RB_FIND(name, root, key) \
    name##_find(root, key)

#define RB_INSERT(name, root, entry) \
    name##_insert(root, entry)
