#!/usr/bin/env ksh

#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2012 by Delphix. All rights reserved.
#

. $STF_SUITE/include/libtest.shlib
. $STF_SUITE/tests/functional/nopwrite/nopwrite.shlib

#
# Description:
# Verify that nopwrite works for sync writes
#
# Strategy:
# 1. Create an origin fs with compression and sha256.
# 2. Clone origin such that it inherits the properies.
# 3. Use dd with the sync flag to test the sync write path.
#

verify_runnable "global"
origin="$TESTPOOL/$TESTFS"
log_onexit cleanup

function cleanup
{
	destroy_dataset -R $origin
	log_must $ZFS create -o mountpoint=$TESTDIR $origin
}

log_assert "nopwrite works for sync writes"

log_must $ZFS set compress=on $origin
log_must $ZFS set checksum=sha256 $origin
$GNUDD if=/dev/urandom of=$TESTDIR/file bs=1024k count=$MEGS oflag=sync \
    conv=notrunc >/dev/null 2>&1 || log_fail "dd into $TESTDIR/file failed."
$ZFS snapshot $origin@a || log_fail "zfs snap failed"
log_must $ZFS clone $origin@a $origin/clone

$GNUDD if=/$TESTDIR/file of=/$TESTDIR/clone/file bs=1024k count=$MEGS \
    oflag=sync conv=notrunc >/dev/null 2>&1 || log_fail "dd failed."

log_must verify_nopwrite $origin $origin@a $origin/clone

log_pass "nopwrite works for sync writes"
