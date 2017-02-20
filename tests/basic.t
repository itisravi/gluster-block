#!/bin/env bash
#********************************************************************#
#                                                                    #
# Copyright (c) 2016 Red Hat, Inc. <http://www.redhat.com>           #
# This file is part of gluster-block.                                #
#                                                                    #
# This file is licensed to you under your choice of the GNU Lesser   #
# General Public License, version 3 or any later version (LGPLv3 or  #
# later), or the GNU General Public License, version 2 (GPLv2), in   #
# all cases as published by the Free Software Foundation.            #
#                                                                    #
#                                                                    #
# Run:   (Make sure you have all the dependent binaries installed)   #
# $ ./tests/basic.t                                                  #
#                                                                    #
#********************************************************************#


HOST=$(hostname)
VOLNAME="block-test"
BLKNAME="sample-block"
BRKDIR="/tmp/block/"


function TEST()
{
  echo "TEST : $@"
  eval $@
  if [ $? -ne 0 ]; then
    echo -e "line $(caller | awk '{print $1}') : NOT OK\n"
    exit 1;
  fi
  echo -e "line $(caller | awk '{print $1}') : OK\n"
}


function cleanup()
{
  echo -e "\nRunning test cleanup ..."

  # Block delete
  gluster-block delete ${BLKNAME} volume ${VOLNAME}

  gluster --mode=script vol stop ${VOLNAME}
  gluster --mode=script vol del ${VOLNAME}

  rm -rf ${BRKDIR}
}


function force_terminate()
{
  local ret=$?;
  >&2 echo -e "\nreceived external"\
              "signal --$(kill -l $ret)--, calling 'cleanup' ...\n";
  cleanup;
  exit $ret;
}


trap force_terminate INT TERM HUP

pidof glusterd 2>&1 >/dev/null
if [ $? -eq 1 ]; then
  TEST glusterd
fi

# Create gluster volume
TEST gluster vol create ${VOLNAME} ${HOST}:${BRKDIR} force

# Start the volume
TEST gluster vol start ${VOLNAME}

# Start gluster-blockd.service
systemctl daemon-reload
TEST systemctl restart gluster-blockd.service
sleep 1;

# Block create
TEST gluster-block create ${BLKNAME} volume ${VOLNAME} size 1GiB mpath 1 servers ${HOST}

# Block list
TEST gluster-block list volume ${VOLNAME}

# Block info
TEST gluster-block info ${BLKNAME} volume ${VOLNAME}

cleanup;