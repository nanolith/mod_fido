/**
 * \file models/shadow/kernel/tty_create_random.c
 *
 * \brief Shadow implementation of tty_create_random.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_retval();

struct tty dummy_tty;

struct tty* tty_create_random()
{
    if (0 == nondet_retval())
    {
        return &dummy_tty;
    }
    else
    {
        return NULL;
    }
}
