#include <iostream>
#include "main.h"
#include "libusb.h"

int main() {

    std::cout << "<-- KD2YKG Decoder -->" << std::endl;

    usbController.init();

    libusb_device *rtl_sdr = usbController.getRTLSDR();
    libusb_context *usbCtx = usbController.getContext();

    usbController.printDevicesInfo(rtl_sdr);

    return 0;
}
