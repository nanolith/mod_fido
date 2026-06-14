/**
 * \file models/shadow/kernel/property_error_code_is_expected_for_file_close.c
 *
 * \brief Verify that the error code comes unfiltered from the original file
 * close method in pts.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

extern int fileops_default_close_return_value;

bool property_error_code_is_expected_for_file_close(int error)
{
    return error == fileops_default_close_return_value;
}
