/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (C) 2008-2010 Lawrence Livermore National Security, LLC.
 * Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 * Written by Brian Behlendorf <behlendorf1@llnl.gov>.
 * LLNL-CODE-403049.
 */

#ifndef _SYS_VDEV_IOKIT_H
#define	_SYS_VDEV_IOKIT_H

#ifdef _KERNEL
#include <sys/vdev.h>
#include <sys/zio.h>

#ifdef __cplusplus
#include <IOKit/storage/IOBlockStorageDevice.h>
#include <IOKit/storage/IOMedia.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOMemoryDescriptor.h>

typedef struct vdev_iokit_context {
    IOMemoryDescriptor *      buffer;
    IOStorageCompletion             completion;
    zio_t *                         zio;
} vdev_iokit_context_t;

#endif /* C++ */

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

typedef struct vdev_iokit {
    uintptr_t *     vd_iokit_hl;        /* IOMedia service handle */
    uintptr_t *     vd_zfs_hl;          /* IOProvider zfs handle */
	boolean_t       vd_offline;         /* device has gone offline */
    void *          in_command_pool;    /* IOCommandPool for reads */
    void *          out_command_pool;   /* IOCommandPool for writes */
    void *          command_set;        /* OSSet to hold all commands */
//  uint64_t        vd_ashift;          /* ashift alignment */
} vdev_iokit_t;

/*
 * C language interfaces
 */

extern void vdev_iokit_log(const char *);
extern void vdev_iokit_log_str(const char *, const char *);
extern void vdev_iokit_log_ptr(const char *, const void *);
extern void vdev_iokit_log_num(const char *, const uint64_t);
    
void vdev_iokit_alloc(vdev_t *);
    
void vdev_iokit_free(vdev_t *);
    
extern void vdev_iokit_hold(vdev_t *);
    
extern void vdev_iokit_rele(vdev_t *);
    
extern void vdev_iokit_state_change(vdev_t *, int, int);

extern int vdev_iokit_open_by_path(vdev_t *, char *);

extern int vdev_iokit_find_by_path(vdev_t *, char *);

extern int vdev_iokit_find_by_guid(vdev_t *);
    
extern int vdev_iokit_physpath(vdev_t *, char *);

extern int vdev_iokit_open(vdev_t *, uint64_t *, uint64_t *, uint64_t *);

extern void vdev_iokit_close(vdev_t *);

extern int vdev_iokit_handle_open(vdev_t *);

extern int vdev_iokit_handle_close(vdev_t *);

extern int vdev_iokit_sync(vdev_t *, zio_t *);

extern int vdev_iokit_get_size(vdev_t *, uint64_t *, uint64_t *, uint64_t *);
    
extern int vdev_iokit_status(vdev_t *);
    
extern int vdev_iokit_ioctl(vdev_t *, zio_t *);

extern void vdev_iokit_ioctl_done(void *, const int);
    
extern int vdev_iokit_strategy(vdev_t *, zio_t *);

extern void vdev_iokit_io_intr(void *, void *, kern_return_t, UInt64);

#if 0
/* Extern for raidz dumps, not needed */
extern int vdev_iokit_physio(vdev_t *,
                            caddr_t, size_t, uint64_t, int, boolean_t);
#endif /* disabled */
    
/*
 * Since vdev_iokit.c is not compiled into libzpool, this function should only be
 * defined in the zfs kernel module.
 */
#ifdef _KERNEL
#if 0
    extern int vdev_iokit_physio(uintptr_t *, caddr_t, size_t, uint64_t, int);
#endif /* disabled */
#endif
    
#ifdef __cplusplus
}   /* extern "C" */
#endif /* C++ */

#endif /* _KERNEL */
#endif /* _SYS_VDEV_IOKIT_H */