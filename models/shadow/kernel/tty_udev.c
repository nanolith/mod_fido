/**
 * \file models/shadow/kernel/tty_udev.c
 *
 * \brief Shadow implementation of \ref tty_udev.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

dev_t nondet_dev();

dev_t tty_udev(struct tty *tp)
{
    return nondet_dev();
}
