/**
 * \file models/shadow/mod_fido/mod_fido_instance_ioctl_tty_get.c
 *
 * \brief Shadow implementation of mod_fido_instance_ioctl_tty_get.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

struct tty*
mod_fido_instance_ioctl_tty_get(
    mod_fido_instance* inst, struct thread *td, struct ioctl_args* args)
{
    struct tty* tp = NULL;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        mod_fido_instance_ioctl_tty_get, inst, td, args);

    tp = tty_create_random();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        mod_fido_instance_ioctl_tty_get, tp, inst, td, args);

    return tp;
}
