/**
 * \file models/shadow/kernel/vnode_create_random.c
 *
 * \brief Shadow implementation of vnode_create_random.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();
int nondet_int();

struct vnode* vnode_create_random()
{
    struct vnode* retval;

    if (0 == nondet_retval())
    {
        retval =
            (struct vnode*)malloc(
                sizeof(struct vnode), M_FIDO, M_WAITOK | M_ZERO);
        if (NULL == retval)
        {
            /* trim branch. */
            MODEL_ASSUME(0);
        }

        retval->v_type = nondet_int();
        retval->v_rdev = NULL;
        if (VCHR == retval->v_type)
        {
            retval->v_rdev = cdev_create_random();
        }

        return retval;
    }
    else
    {
        return NULL;
    }
}
