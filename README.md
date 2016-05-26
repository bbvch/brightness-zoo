[![Build Status](https://travis-ci.org/bbvch/brightness-zoo.svg?branch=master)](https://travis-ci.org/bbvch/brightness-zoo)

A set of services to control the backlight in embedded systems.

Automatic tests
===============

- Acceptance tests are in the directory `features`.
- Unit tests are in the corresponding directory with the names `*.test`.

See `ci/test.sh` for instructions.

Manual tests
============

- Configure the power save brightness percentage to 75 in the brightnessd configuration file
- Start brightnessd with a device
- Configure the maximal brightness to 84 in the ambientlightd configuration file
- Configure the maximal lux to something you can provide
- Configure the update interval to 5 seconds
- Start ambientlightd with a device
- Cover the ambient light sensor
- Check that the brightness went to 10%
- Give full light to the ambient light sensor
- Check that the brightness went to 84% in less or equal 5 seconds
- Stop ambientlightd
- Configure the activity timeout to 10 seconds in the xactivityd configuration file
- Start xactivityd
- Check that after 10 seconds of inactivity the brightness went to 75%
- Stop everything

