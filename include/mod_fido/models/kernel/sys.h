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
#include <limits.h>
#include <pthread.h>
#include <mod_fido/properties/kernel.h>

#define MALLOC_DECLARE(x) extern const int x

typedef int module_t;

typedef int (sy_call_t)(struct thread* td, void* args);

struct mtx
{
    pthread_mutex_t mtx;
    int valid;
    int locked;
};

struct tty
{
};

dev_t tty_udev(struct tty *tp);

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

struct ucred
{
    uid_t cr_ruid;
};

struct thread
{
    struct proc* td_proc;
    struct ucred* td_ucred;
};

struct ioctl_args
{
    int fd;
    int com;
    const void* data;
};

typedef int (*fo_close_t)(struct file*, struct thread*);

struct fileops
{
    fo_close_t fo_close;
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

struct file
{
    int f_type;
    void* f_data;
    struct fileops* f_ops;
};

int fget(
    struct thread* td, int fd, const cap_rights_t* rightsp, struct file** fpp);
void fdrop(struct file* fp, struct thread* td);

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
    int caps;
};

cap_rights_t* cap_rights_init(cap_rights_t *rights, int capability);

#define CAP_IOCTL 1

#define DTYPE_VNODE 1
#define DTYPE_PTS 2

int	priv_check(struct thread *td, int priv);

#define PRIV_DRIVER 100

sbintime_t getsbinuptime(void);

int copyin(const void *uaddr, void *kaddr, size_t len);

#define	IOC_VOID 0x20000000UL
#define	IOC_OUT  0x40000000UL
#define	IOC_IN   0x80000000UL
struct cdev* cdev_create_random();
struct tty* tty_create_random();
struct vnode* vnode_create_random();
int fileops_default_close(struct file* fp, struct thread* td);
