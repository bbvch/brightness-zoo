# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess
import dbus
import time

@given(u'I start brightnessd with the device "{device}"')
def step_impl(context, device):
	device = context.tmpdir + '/' + device;
	context.application = subprocess.Popen(['brightnessd', '--device=' + device])

	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.brightness') in bus.list_names()):
		time.sleep(0.01)

