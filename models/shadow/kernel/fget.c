/**
 * \file models/shadow/kernel/fget.c
 *
 * \brief Shadow implementation of fget.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

struct fileops dummy_fileops = {
    .fo_close = &fileops_default_close
};

int fget(
    struct thread* td, int fd, const cap_rights_t* rightsp, struct file** fpp)
{
    int retval = nondet_retval();

    if (0 == retval)
    {
        *fpp = (struct file*)malloc(sizeof(**fpp), M_FIDO, M_WAITOK | M_ZERO);
        if (NULL == *fpp)
        {
            /* trim this branch. */
            MODEL_ASSUME(0);
        }

        (*fpp)->f_type = nondet_retval();
        (*fpp)->f_ops = &dummy_fileops;
        (*fpp)->f_data = NULL;

        if (DTYPE_VNODE == (*fpp)->f_type)
        {
            (*fpp)->f_data = vnode_create_random();
        }
        else if (DTYPE_PTS == (*fpp)->f_type)
        {
            (*fpp)->f_data = tty_create_random();
        }
    }

    return retval;
}
