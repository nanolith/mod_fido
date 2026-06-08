/**
 * \file malloc_arena.c
 *
 * \brief The mod_fido malloc arena definition.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

MALLOC_DEFINE(M_FIDO, "mod_fido", "fido (Filtered Do) malloc arena"); 
