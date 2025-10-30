#!/bin/bash

set -e

# Change to build directory
cd build

# unit tests
ambientlightd/ambientlightd.test
brightnessd/brightnessd.test
common/common.test


# start DBus
if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
	eval `dbus-launch --sh-syntax`
fi

# set paths
export PATH=`pwd`/ambientlightd:${PATH}
export PATH=`pwd`/brightnessd:${PATH}
export PATH=`pwd`/checkbrightness:${PATH}

# Go to features directory (relative to project root)
cd ../features

# acceptance tests
behave

