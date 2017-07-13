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

	return subprocess.Popen(arguments, env=environment, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=-1)


def waitForDbusService():
	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.brightness') in bus.list_names()):
		time.sleep(0.01)


@given(u'I start brightnessd with the device "{device}"')
def step_impl(context, device):
	device = context.tmpdir + '/' + device
	context.brightnessd = startApplication(context, ['brightnessd', '--session', '--device=' + device])
	waitForDbusService()


@given(u'I start dummy-brightnessd')
def step_impl(context):
	context.brightnessd = startApplication(context, ['python', 'steps/dummy-brightnessd.py'])
	waitForDbusService()

@when(u'I run ambientlightd with the device "{device}" and argument "{arg1}"')
def step_impl(context, device, arg1):
	device = context.tmpdir + '/' + device
	context.ambientlightd = startApplication(context, ['ambientlightd', '--session', '--single', '--device=' + device, arg1])
	context.stdout = context.ambientlightd.stdout.read()
	context.stderr = context.ambientlightd.stderr.read()
	context.ambientlightd.wait()

@when(u'I run ambientlightd with the device "{device}"')
def step_impl(context, device):
	device = context.tmpdir + '/' + device
	context.ambientlightd = startApplication(context, ['ambientlightd', '--session', '--single', '--device=' + device])
	context.ambientlightd.wait()
	context.stdout = context.ambientlightd.stdout.read()
	context.stderr = context.ambientlightd.stderr.read()

@when(u'I run ambientlightd with the argument "{arg1}"')
def step_impl(context, arg1):
	context.ambientlightd = startApplication(context, ['ambientlightd', '--session', arg1])
	context.ambientlightd.wait()
	context.stdout = context.ambientlightd.stdout.read()
	context.stderr = context.ambientlightd.stderr.read()

@then(u'I expect the string "{text}" on stderr from ambientlightd')
def step_impl(context, text):
	assert context.stderr.find(text) != -1, 'expected to see "' + text + '", got: \n' + output

@then(u'I expect the string "{text}" on stdout from ambientlightd')
def step_impl(context, text):
	assert context.stdout.find(text) != -1, 'expected to see "' + text + '", got: \n' + output

@then(u'I expect the string "{text}" on stderr from brightnessd')
def step_impl(context, text):
	output = context.brightnessd_stderr
	assert output.find(text) != -1, 'expected to see "' + text + '", got: \n' + output

@then(u'brightnessd exits with the error code -6')
def step_impl(context):
	context.brightnessd.wait()
	context.brightnessd_stderr = context.brightnessd.stderr.read()
	code = context.brightnessd.returncode
	assert code == 256-6, 'expected to see "' + str(-6) + '", got: ' + str(code)


