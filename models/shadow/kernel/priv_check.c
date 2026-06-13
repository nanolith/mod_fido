/**
 * \file models/shadow/kernel/priv_check.c
 *
 * \brief Shadow implementation of \ref priv_check.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int nondet_int();

int	priv_check(struct thread *td, int priv)
{
    return nondet_int();
}
