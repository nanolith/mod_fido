/**
 * \file models/shadow/kernel/property_ioctl_args_valid.c
 *
 * \brief Check if a set of ioctl args are valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Returns true if the given ioctl args are valid.
 *
 * \param args              The arguments to check.
 *
 * \returns true if these arguments are valid.
 */
bool property_ioctl_args_valid(const struct ioctl_args* args)
{
    return true;
}
