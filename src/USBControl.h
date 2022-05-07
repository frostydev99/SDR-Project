//
// Created by Blind on 5/6/2022.
//

#ifndef SDRDECODER_USBCONTROL_H
#define SDRDECODER_USBCONTROL_H

#include "iostream"
#include "libusb.h"

class USBControl {


    public:
        USBControl();
        void init();
        void listDevices();
        libusb_device* getRTLSDR();
        void printDevicesInfo(libusb_device*);
        libusb_context* getContext();

    private:
        libusb_context *usbContext{};
        libusb_device **list = nullptr;
        libusb_device *device = nullptr;
        libusb_device_handle *handler{};
        libusb_device *rtlSdr = nullptr;
};



#endif //SDRDECODER_USBCONTROL_H
