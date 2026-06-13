/**
 * \file models/shadow/kernel/property_file_handle_valid.c
 *
 * \brief Check to see if a file handle is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

/**
 * \brief Returns true if the given file handle is valid.
 *
 * \param fp                The handle to check.
 *
 * \returns true if this handle is valid.
 */
bool property_file_handle_valid(const struct file* fp)
{
    return NULL != fp;
}
