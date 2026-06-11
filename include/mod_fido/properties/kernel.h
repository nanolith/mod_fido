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
