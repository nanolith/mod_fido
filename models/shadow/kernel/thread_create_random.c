/**
 * \file models/shadow/kernel/thread_create_random.c
 *
 * \brief Helpers to create and release thread instances.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

int thread_create_random(struct thread** td)
{
    *td = (struct thread*)malloc(sizeof(**td), M_FIDO, M_WAITOK | M_ZERO);
    if (NULL == *td)
    {
        return 1;
    }

    /* should we create a proc? */
    if (0 == nondet_int())
    {
        (*td)->td_proc =
            (struct proc*)malloc(
                sizeof(struct proc), M_FIDO, M_WAITOK | M_ZERO);
        if (NULL == (*td)->td_proc)
        {
            /* trim this branch. */
            MODEL_ASSUME(0);
        }

        /* should we create a session? */
        if (0 == nondet_int())
        {
            (*td)->td_proc->p_session =
                (struct session*)malloc(
                    sizeof(struct session), M_FIDO, M_WAITOK | M_ZERO);
            if (NULL == (*td)->td_proc->p_session)
            {
                /* trim this branch. */
                MODEL_ASSUME(0);
            }

            /* should we create a controlling terminal? */
            if (0 == nondet_int())
            {
                (*td)->td_proc->p_session->s_ttyp =
                    (struct tty*)malloc(
                        sizeof(struct tty), M_FIDO, M_WAITOK | M_ZERO);
                if (NULL == (*td)->td_proc->p_session->s_ttyp)
                {
                    /* trim this branch. */
                    MODEL_ASSUME(0);
                }
            }
            else
            {
                (*td)->td_proc->p_session->s_ttyp = NULL;
            }
        }
        else
        {
            (*td)->td_proc->p_session = NULL;
        }
    }
    else
    {
        (*td)->td_proc = NULL;
    }

    return 0;
}

void thread_release(struct thread* td)
{
    if (NULL != td->td_proc)
    {
        if (NULL != td->td_proc->p_session)
        {
            if (NULL != td->td_proc->p_session->s_ttyp)
            {
                free(td->td_proc->p_session->s_ttyp, M_FIDO);
            }

            free(td->td_proc->p_session, M_FIDO);
        }

        free(td->td_proc, M_FIDO);
    }

    free(td);
}
