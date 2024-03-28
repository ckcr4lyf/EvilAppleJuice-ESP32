# EvilAppleJuice ESP32

Spam BLE advertisements on iPhones!

|iPhone 15s (latest)|Older iPhones|
|-------------------|-------------|
|<video controls width="250" src="https://user-images.githubusercontent.com/6680615/274864225-53ed6d7c-0569-4f22-b55b-bc9973c4bc93.mp4"></video>|<video controls width="250" src="https://user-images.githubusercontent.com/6680615/274864287-c6e871fd-9fdf-4507-ae21-a566beead5cc.mp4"></video>|

Based off of the work of [ronaldstoner](https://github.com/ronaldstoner) in the [AppleJuice repository](https://github.com/ECTO-1A/AppleJuice/blob/e6a61f6a199075f5bb5b1a00768e317571d25bb9/ESP32-Arduino/applejuice.ino).

Also thanks to [simondankelmann](https://github.com/simondankelmann) for their discoveries in new advertising messages to pop-up new notifications in iOS devices [source](https://github.com/simondankelmann/Bluetooth-LE-Spam/blob/main/app/src/main/java/de/simon/dankelmann/bluetoothlespam/AdvertisementSetGenerators/ContinuityActionModalAdvertisementSetGenerator.kt)

With the randomization optimizations it can render an iPhone almost useless with a single ESP32 (a new notification as soon as you close the old one).

Confirmed on:
* iPhone 15 (running iOS 17.1.2)
* iPhone 14 Pro Max (running iOS 17.2 b3) (See #19)
* iPhone 14 Pro (running iOS 16.6.1)
* iPhone 13 Pro (running iOS 17.4 (21E5184k))
* iPhone 11 (running iOS 16.6.1)
* iPhone X (running iOS 14.8 (18H17)) - only "AppleTV Keyboard", "TV Color Balance", "AppleTV Setup", "AppleTV Homekit Setup", "AppleTV New User".
* iPad Pro 11 (running iPadOS 17.3 (21D50))

Not working on:
* iPhone 4S (running iOS 10.3 (14E277))

Other observations:
* Doesn't seem to spawn notifications if Keyboard is open / Camera is open

### Video Demo

Single ESP32 vs. iPhone 14 Pro @ iOS 16.6.1

https://github.com/ECTO-1A/AppleJuice/assets/6680615/47466ed6-03c9-43b2-a0d0-aac2e2aaa228

## Notable Differences

This implementation makes the following changes:

* Random source MAC address (including `BLE_ADDR_TYPE_RANDOM`)
* Randomly pick BLE Advertisement Type ([this may lead to more success](https://github.com/ECTO-1A/AppleJuice/pull/25))
* Randomly pick one of the possible devices
* Sets the ESP32 BLE Power to the maximum (9dBm) to increase range

And it makes these random choices every time it runs (default re-advertise every second).

Given the 29 devices and the 3 advertisement types, there are a total of 87 unique possible advertisements (ignoring the random source MAC) possible, of which one is broadcast every second.

## Compatibility

This project has been tested on:

+ [ESP32-C3 from AirM2M](https://wiki.luatos.com/chips/esp32c3/board.html).
+ [M5Stick-C](https://shop.m5stack.com/products/stick-c)

## How to use

This project offers an easy way to update your ESP32 device with the latest firmware, catering to both technical and less technical users. Here's how you can get started:

### Quick Start with Pre-compiled Firmware

1. **Download the Firmware**: Go to the [Releases](https://github.com/ckcr4lyf/EvilAppleJuice-ESP32/releases/tag/latest) section of this GitHub repository and download the latest `.bin` file.
2. **Connect Your Device**: Make sure your ESP32 device is connected to your computer via USB.
3. **Flash the Firmware**:
    - **Using webesp**: Navigate to the online esptool (eg: <https://lsong.org/webesp>), select your `.bin` file, and follow the instructions to flash your device directly from your browser.
    - **Using esptool**: Open a command line or terminal. Execute the following command, replacing `<YourSerialPort>` with your device's serial port and `<FirmwareFile.bin>` with the path to your downloaded `.bin` file:
      ```shell
      esptool.py --port /dev/cu.usbserial-xxx write_flash 0x10000 ~/Downloads/EvilAppleJuice-ESP32-esp32dev-20240328.bin
      ```

This method is straightforward and does not require in-depth programming knowledge, making it accessible for everyone.

### Build from Source

If you prefer to compile the firmware yourself or wish to contribute to the project, here's how you can set up your environment:

1. **Clone the Repository**: Use your preferred method to clone this repository to your local machine.
2. **Setup Your Development Environment**: Download and install Visual Studio Code (VS Code) and the PlatformIO extension. This setup is recommended for compiling and uploading the firmware to your ESP32 device.
3. **Open the Project in VS Code**: Navigate to the cloned project folder and open it in VS Code. PlatformIO will automatically handle the project configuration.
4. **Upload the Firmware**: With your ESP32 device connected to your computer, use the PlatformIO interface in VS Code to compile and upload the firmware.

Happy hacking :>

---