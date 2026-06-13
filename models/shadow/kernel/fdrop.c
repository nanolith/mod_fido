/**
 * \file models/shadow/kernel/fdrop.c
 *
 * \brief Shadow implementation of fdrop.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

void fdrop(struct file* fp, struct thread* td)
{
    if (DTYPE_VNODE == fp->f_type && NULL != fp->f_data)
    {
        struct vnode* vp = fp->f_data;
        if (NULL != vp && VCHR == vp->v_type)
        {
            struct cdev* dev = vp->v_rdev;
            free(dev);
        }

        free(vp);
    }

    free(fp);
}
