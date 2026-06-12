/**
 * \file models/kernel/sys.h
 *
 * \brief Simplified system declarations for model checking.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <pthread.h>
#include <mod_fido/properties/kernel.h>

#define MALLOC_DECLARE(x) extern const int x

typedef void sy_call_t;

struct mtx
{
    pthread_mutex_t mtx;
    int valid;
    int locked;
};

struct fileops
{
};

struct sysent {
    sy_call_t* sy_call;
};

extern struct sysent sysent[];

#define M_WAITOK 1
#define M_ZERO   2
#define MTX_DEF 1
