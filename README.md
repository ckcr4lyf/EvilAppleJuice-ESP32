# EvilAppleJuice ESP32

Based off of the work of [ronaldstoner](https://github.com/ronaldstoner) in the [AppleJuice repository](https://github.com/ECTO-1A/AppleJuice/blob/e6a61f6a199075f5bb5b1a00768e317571d25bb9/ESP32-Arduino/applejuice.ino).

With the randomization optimizations it can render an iPhone almost useless with a single ESP32 (a new notification as soon as you close the old one).

Confirmed on:
* iPhone 14 Pro (running iOS 16.6.1)
* iPhone 11 (running iOS 16.6.1)

### Video Demo

Single ESP32 vs. iPhone 14 Pro @ iOS 16.6.1

https://github.com/ECTO-1A/AppleJuice/assets/6680615/47466ed6-03c9-43b2-a0d0-aac2e2aaa228

## Notable Differences

This implementation makes the following changes:

* Random source MAC address (including `BLE_ADDR_TYPE_RANDOM`)
* Randomly pick BLE Advertisement Type ([this may lead to more success](https://github.com/ECTO-1A/AppleJuice/pull/25))
* Randomly pick one of the possible devices

And it makes these random choices every time it runs (default re-advertise every second).

Given the 29 devices and the 3 advertisement types, there are a total of 87 unique possible advertisements (ignoring the random source MAC) possible, of which one is broadcast every second.

## Usage

Clone the repo, and easiest would be to use VS Code w/ PlatformIO to upload it to your ESP32.

This project has been tested on an [ESP32-C3 from AirM2M](https://wiki.luatos.com/chips/esp32c3/board.html).

