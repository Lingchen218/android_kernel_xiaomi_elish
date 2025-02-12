/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2020 Google LLC
 */
#include <linux/fs.h>
#include <linux/dcache.h>
#ifndef _INCFS_PSEUDO_FILES_H
#define _INCFS_PSEUDO_FILES_H

#define PSEUDO_FILE_COUNT 3
#define INCFS_START_INO_RANGE 10

int dir_lookup_pseudo_files(struct super_block *sb, struct dentry *dentry);
int emit_pseudo_files(struct dir_context *ctx);
static ssize_t log_read(struct file *f, char __user *buf, size_t len,
	loff_t *ppos);

#endif

#include <linux/file.h>

#include <linux/namei.h>
#include <linux/poll.h>
#include <linux/syscalls.h>
#include <uapi/linux/incrementalfs.h>


#include "data_mgmt.h"
#include "format.h"
#include "integrity.h"
#include "vfs.h"
/* State of an open .pending_reads file, unique for each file descriptor. */
struct pending_reads_state {
	/* A serial number of the last pending read obtained from this file. */
	int last_pending_read_sn;
};

/* State of an open .log file, unique for each file descriptor. */
struct log_file_state {
	struct read_log_state state;
};