//
// Created by Blind on 5/6/2022.
//

#include "USBControl.h"



USBControl::USBControl() {}

void USBControl::init() {
    try {
        int init = libusb_init(&usbContext);

        if(init == 0) {
            std::cout << "LibUSB: Initialized" << std::endl;
        }
    } catch(libusb_error) {
        std::cout << "LibUSB: Failed to init!" << std::endl;
    }
}



void USBControl::listDevices() {
    ssize_t listRt = libusb_get_device_list(usbContext, &list);
    if(listRt <= 0) {
        std::cout << "LibUSB: Unable to get device list!";
        libusb_free_device_list(list, 1);
        libusb_exit(usbContext);
        return;
    }

    for(int i=0; i < listRt; i++) {
        device = list[i];
        struct libusb_device_descriptor desc{};

        std::cout << "Device <-- " << i << " -->" << std::endl;

        if(!device) {
            std::cout << "LibUSB: Unable to find device!" << std::endl;
            libusb_free_device_list(list, 1);
            libusb_exit(usbContext);
            return;
        }

        int devAddr = libusb_get_device_address(device);

        int descRt = libusb_get_device_descriptor(device, &desc);
        if(descRt < 0) {
            std::cout << "LibUSB: Unable to get description!" << std::endl;
            libusb_free_device_list(list, 1);
            libusb_exit(usbContext);
            return;
        }



        std::cout << "  Device Address: " << devAddr << std::endl;
        //std::cout << "  Product ID: " << std::hex << desc.idProduct << std::endl;
        //std::cout << "  Vendor ID: " << std::hex << desc.idVendor << std::endl;
        std::cout << "  Product ID: " << desc.idProduct << std::endl;
        std::cout << "  Vendor ID: " << desc.idVendor << std::endl;
        //std::cout << "  Device Name: " << humanizer.findByProductId(desc.idProduct) << std::endl;
    }

}

libusb_device* USBControl::getRTLSDR() {
    ssize_t listRt = libusb_get_device_list(usbContext, &list);
    if(listRt <= 0) {
        std::cout << "LibUSB: Unable to get device list!";
        libusb_free_device_list(list, 1);
        libusb_exit(usbContext);
    }

    for(int i=0; i < listRt; i++) {
        device = list[i];
        struct libusb_device_descriptor desc{};

        if (!device) {
            std::cout << "LibUSB: Unable to find device!" << std::endl;
            libusb_free_device_list(list, 1);
            libusb_exit(usbContext);
        }

        int descRt = libusb_get_device_descriptor(device, &desc);
        if (descRt < 0) {
            std::cout << "LibUSB: Unable to get description!" << std::endl;
            libusb_free_device_list(list, 1);
            libusb_exit(usbContext);
        }

        if(desc.idProduct == 0x2838 && desc.idVendor == 0x0BDA) {
            rtlSdr = device;
        }

        return rtlSdr;
    }
}

void USBControl::printDevicesInfo(libusb_device *) {
    struct libusb_device_descriptor desc{};

    if (!device) {
        std::cout << "LibUSB: Unable to find device!" << std::endl;
        libusb_free_device_list(list, 1);
        libusb_exit(usbContext);
    }

    int devAddr = libusb_get_device_address(device);

    int descRt = libusb_get_device_descriptor(device, &desc);
    if (descRt < 0) {
        std::cout << "LibUSB: Unable to get description!" << std::endl;
        libusb_free_device_list(list, 1);
        libusb_exit(usbContext);
    }

    std::cout << "<-- " << &device << "-->" << std::endl;
    std::cout << "  Device Address: " << devAddr << std::endl;
    std::cout << "  Product ID: " << desc.idProduct << std::endl;
    std::cout << "  Vendor ID: " << desc.idVendor << std::endl;
}

libusb_context *USBControl::getContext() {
    return this->usbContext;
}
