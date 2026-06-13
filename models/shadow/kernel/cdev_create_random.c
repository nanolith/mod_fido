/**
 * \file models/shadow/kernel/cdev_create_random.c
 *
 * \brief Shadow implementation of cdev_create_random.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

struct cdev* cdev_create_random()
{
    struct cdev* retval;

    if (0 == nondet_retval())
    {
        retval =
            (struct cdev*)malloc(
                sizeof(struct cdev), M_FIDO, M_WAITOK | M_ZERO);
        if (NULL == retval)
        {
            /* trim branch. */
            MODEL_ASSUME(0);
        }

        retval->si_drv1 = tty_create_random();

        return retval;
    }
    else
    {
        return NULL;
    }
}
