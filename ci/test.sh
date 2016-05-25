#!/bin/bash

set -e

# unit tests
ambientlightd/ambientlightd.test
brightnessd/brightnessd.test
common/common.test
xactivityd/xactivityd.test


# start DBus
if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
	eval `dbus-launch --sh-syntax`
fi

# set paths
export PATH=`pwd`/ambientlightd:${PATH}
export PATH=`pwd`/brightnessd:${PATH}
cd features

# acceptance tests
behave

