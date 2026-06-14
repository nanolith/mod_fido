/**
 * \file models/shadow/kernel/getsbinuptime.c
 *
 * \brief Shadow implementation of \ref getsbinuptime.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

sbintime_t nondet_time();

sbintime_t getsbinuptime(void)
{
    return nondet_time();
}
