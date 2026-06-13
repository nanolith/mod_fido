/**
 * \file mod_fido_instance_ioctl_tty_get.c
 *
 * \brief Attempt to get the tty for the ioctl call.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Try to get the tty pointer from a given set of ioctl args.
 *
 * \note As a side-effect, this method will hook a pseudo-terminal for further
 * processing.
 *
 * \param inst          The mod_fido instance for this handler.
 * \param td            The thread on which this system call was made.
 * \param args          The arguments for this system call.
 *
 * \returns the tty for this ioctl if found, or NULL if not found.
 */
struct tty*
mod_fido_instance_ioctl_tty_get_locked(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args)
{
    int retval;
    struct tty* tp = NULL;
    struct file* fp;
    struct vnode* vp;
    struct cdev* dev;
    cap_rights_t rights;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_tty_get_locked, inst, td, args);

    /* attempt to get the file handle for this descriptor. */
    retval = fget(td, args->fd, cap_rights_init(&rights, CAP_IOCTL), &fp);
    if (0 == retval)
    {
        /* Is this a physical hardware line / console? */
        if (DTYPE_VNODE == fp->f_type)
        {
            vp = fp->f_data;
            if (NULL != vp && VCHR == vp->v_type)
            {
                dev = vp->v_rdev;
                if (NULL != dev)
                {
                    tp = dev->si_drv1;
                }
            }
        }
        /* Is this a pseudo-terminal? */
        else if (DTYPE_PTS == fp->f_type)
        {
            tp = fp->f_data;
            if (tp != NULL)
            {
                /* hook our close tracker to the file pointer. */
                mod_fido_instance_hook_pts_fops_locked(inst, fp);
            }
        }

        /* drop this file handle reference. */
        fdrop(fp, td);
    }

    /* if tp is null, then get the controlling terminal. */
    if (NULL == tp)
    {
        struct proc *p = td->td_proc;
        if (NULL != p)
        {
            PROC_LOCK(p);
            if (NULL != p->p_session)
            {
                SESS_LOCK(p->p_session);
                tp = p->p_session->s_ttyp;
                SESS_UNLOCK(p->p_session);
            }
            PROC_UNLOCK(p);
        }
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_tty_get_locked, tp, inst, td, args);

    return tp;
}
