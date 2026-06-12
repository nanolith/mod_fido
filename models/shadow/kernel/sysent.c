/**
 * \file models/shadow/kernel/sysent.c
 *
 * \brief sysent array.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/* forward decls. */
static int
sysent_ioctl(struct thread *td, void *args);

struct sysent sysent[MAX_SYSENT_ENTRIES] = {
    /* SYS_ioctl */
    { .sy_call = &sysent_ioctl },
    /* unknown syscall 1. */
    { .sy_call = NULL },
    /* unknown syscall 2. */
    { .sy_call = NULL },
};

static int nondet_retval();

/* dummy ioctl handler. */
static int
sysent_ioctl(struct thread *td, void *args)
{
    return nondet_retval();
}
