# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import time
import subprocess

@when(u'I set the D-Bus property "percentage" to {value:d} of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"')
def step_impl(context, value):
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.brightness', '/ch/bbv/brightness')
	streetlightd.Set('ch.bbv.brightness.power', 'percentage', dbus.Int32(value), dbus_interface=dbus.PROPERTIES_IFACE)

