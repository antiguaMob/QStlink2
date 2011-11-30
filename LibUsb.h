/*
 * Copyright (c) 2011 Darren Hague & Eric Brandt
 *               Modified to suport Linux and OSX by Mark Liversedge
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef gc_LibUsb_h
#define gc_LibUsb_h

#include <QString>
#include <QDebug>
#include <usb.h> // for the constants etc
#include <QByteArray>
#include <QtEndian>

#define USB_ST_VID 0x0483
#define USB_STLINK_PID 0x3744
#define USB_STLINKv2_PID 0x3748
#define USB_CONFIGURATION  1   /* The sole configuration. */
#define USB_PIPE_IN 0x81	   /* Bulk output endpoint for responses */
#define USB_PIPE_OUT  0x02	   /* Bulk input endpoint for commands */
#define USB_PIPE_ERR 0x83	   /* An apparently-unused bulk endpoint. */
#define USB_TIMEOUT_MSEC 100

class LibUsb {

public:
    LibUsb();

public slots:
    int open();
    void close();
    int read(QByteArray *buf, int bytes);
    int write(QByteArray *buf, int bytes);

private:
    struct usb_dev_handle* OpenAntStick();
    struct usb_interface_descriptor* usb_find_interface(struct usb_config_descriptor* config_descriptor);
    struct usb_dev_handle* device;
    struct usb_interface_descriptor* intf;

    int readEndpoint, writeEndpoint;
    int interface;
    int alternate;
};
#endif