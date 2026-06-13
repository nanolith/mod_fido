/**
 * \file mod_fido/properties/kernel.h
 *
 * \brief Model checking properties for kernel objects.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stdbool.h>

extern int kernel_mtx_valid;

/**
 * \brief Returns true if the given mutex is valid.
 *
 * \param mutex             The mutex to check.
 *
 * \returns true if this mutex is valid.
 */
bool property_mtx_valid(const struct mtx* mutex);

/**
 * \brief Returns true if the given mutex is locked.
 *
 * \param mutex             The mutex to check.
 *
 * \returns true if this mutex is locked.
 */
bool property_mtx_locked(const struct mtx* mutex);

/**
 * \brief Returns true if the given kernel thread is valid.
 *
 * \param td                The thread to check.
 *
 * \returns true if this thread is valid.
 */
bool property_kernel_thread_valid(const struct thread* td);

/**
 * \brief Returns true if the given ioctl args are valid.
 *
 * \param args              The arguments to check.
 *
 * \returns true if these arguments are valid.
 */
bool property_ioctl_args_valid(const struct ioctl_args* args);

/**
 * \brief Returns true if the given file handle is valid.
 *
 * \param fp                The handle to check.
 *
 * \returns true if this handle is valid.
 */
bool property_file_handle_valid(const struct file* fp);
