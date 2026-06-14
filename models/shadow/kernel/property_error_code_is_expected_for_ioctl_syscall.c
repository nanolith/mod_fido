/**
 * \file models/shadow/kernel/property_error_code_is_expected_for_ioctl_syscall.c
 *
 * \brief Verify that the syscall returns an expected error code.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

bool property_error_code_is_expected_for_ioctl_syscall(int error)
{
    return
        (     0 == error
      ||  EBADF == error
      || ENOENT == error
      || ENOTTY == error
      || EINVAL == error
      || EFAULT == error
      ||  EPERM == error);
}
