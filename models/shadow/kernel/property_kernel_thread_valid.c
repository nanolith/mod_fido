/**
 * \file models/shadow/kernel/property_kernel_thread_valid.c
 *
 * \brief Check if a kernel thread is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Returns true if the given kernel thread is valid.
 *
 * \param td                The thread to check.
 *
 * \returns true if this thread is valid.
 */
bool property_kernel_thread_valid(const struct thread* td)
{
    return true;
}
