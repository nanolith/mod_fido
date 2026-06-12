/**
 * \file models/kernel/sys.h
 *
 * \brief Simplified system declarations for model checking.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <errno.h>
#include <pthread.h>
#include <mod_fido/properties/kernel.h>

#define MALLOC_DECLARE(x) extern const int x

typedef int module_t;

typedef void sy_call_t;

struct mtx
{
    pthread_mutex_t mtx;
    int valid;
    int locked;
};

struct tty
{
};

struct session
{
    struct tty* s_ttyp;
};

#define SESS_LOCK(sess)
#define SESS_UNLOCK(sess)

struct proc
{
    struct session* p_session;
};

#define PROC_LOCK(proc)
#define PROC_UNLOCK(proc)

struct thread
{
    struct proc* td_proc;
};

struct ioctl_args
{
    int fd;
};

struct fileops
{
};

struct cdev
{
    struct tty* si_drv1;
};

struct vnode
{
    int v_type;
    struct cdev* v_rdev;
};

#define VCHR 1

struct sysent {
    sy_call_t* sy_call;
};

typedef int (*modeventhand_t)(module_t, int, void*);

typedef struct moduledata moduledata_t;
struct moduledata {
    const char* name;
    modeventhand_t evhand;
    void* priv;
};

#define DECLARE_MODULE(w, x, y, z) REQUIRE_SEMICOLON_HERE

extern struct sysent sysent[];

#define MAX_SYSENT_ENTRIES 3

#define SYS_ioctl 0

#define M_WAITOK 1
#define M_ZERO   2
#define MTX_DEF 1

#define MOD_LOAD 0
#define MOD_UNLOAD 1

typedef struct cap_rights cap_rights_t;
struct cap_rights
{
};

#define CAP_IOCTL 1

#define DTYPE_VNODE 1
#define DTYPE_PTS 2
