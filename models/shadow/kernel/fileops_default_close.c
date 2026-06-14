/**
 * \file models/shadow/kernel/fileops_default_close.c
 *
 * \brief Shadow implementation of the default close method for a file.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int fileops_default_close_return_value = nondet_int();

int fileops_default_close(struct file* fp, struct thread* td)
{
    return fileops_default_close_return_value;
}
