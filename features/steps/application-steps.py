# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess
import dbus
import time
import os

def startApplication(context, arguments):
	environment = dict(os.environ)
	environment["XDG_CONFIG_HOME"] = context.tmpdir

	return subprocess.Popen(arguments, env=environment)


def waitForDbusService():
	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.brightness') in bus.list_names()):
		time.sleep(0.01)


@given(u'I start brightnessd with the device "{device}"')
def step_impl(context, device):
	device = context.tmpdir + '/' + device;
	context.brightnessd = startApplication(context, ['brightnessd', '--device=' + device])
	waitForDbusService()


@given(u'I start dummy-brightnessd')
def step_impl(context):
	context.brightnessd = startApplication(context, ['python', 'steps/dummy-brightnessd.py'])
	waitForDbusService()


@when(u'I run ambientlightd with the device "{device}"')
def step_impl(context, device):
	device = context.tmpdir + '/' + device;
	startApplication(context, ['ambientlightd', '--single', '--device=' + device]).wait();


