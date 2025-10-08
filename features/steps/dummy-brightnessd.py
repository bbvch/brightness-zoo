#!/usr/bin/python

# (C) Copyright 2016
# Urs Fassler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib
import glib

class DummyBrightnessd(dbus.service.Object):
    def __init__(self):
        self.session_bus = dbus.SessionBus()
        self.percentage = -1
        name = dbus.service.BusName("ch.bbv.brightness", bus=self.session_bus)
        dbus.service.Object.__init__(self, name, '/ch/bbv/brightness')

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ss', out_signature='v')
    def Get(self, interface_name, property_name):
        return self.GetAll(interface_name)[property_name]

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ssv')
    def Set(self, interface_name, property_name, value):
        if interface_name == 'ch.bbv.brightness.power':
            if property_name == 'percentage':
                self.percentage = value

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface_name):
        if interface_name == 'ch.bbv.brightness.power':
            return {'percentage': dbus.Int32(self.percentage)}
        else:
            raise dbus.exceptions.DBusException('Unknown interface: ' + interface_name)


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    loop = GLib.MainLoop()
    dummyBrightnessd = DummyBrightnessd()
    loop.run()

