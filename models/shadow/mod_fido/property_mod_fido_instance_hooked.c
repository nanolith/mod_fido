/**
 * \file models/shadow/mod_fido/property_mod_fido_instance_hooked.c
 *
 * \brief Verify that a \ref mod_fido_instance is hooked.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief The \ref mod_fido_instance has been hooked.
 *
 * \param inst          The instance to check.
 *
 * \returns 1 if the instance is hooked and 0 otherwise.
 */
int
property_mod_fido_instance_hooked(
    const mod_fido_instance* inst)
{
    return NULL != inst->old_sys_ioctl;
}
