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

## Usage

Clone the repo, and easiest would be to use VS Code w/ PlatformIO to upload it to your ESP32.

This project has been tested on an [ESP32-C3 from AirM2M](https://wiki.luatos.com/chips/esp32c3/board.html).

### Via Arduino-CLI

#### Windows

If you've setup the Arduino CLI, e.g. via https://wellys.com/posts/esp32_cli/ , then you can `cd` into the `src` folder, and run the following:

```
arduino-cli compile --fqbn esp32:esp32:esp32c6 EvilAppleJuice-ESP32-INO -v
arduino-cli upload -p COM4 --fqbn esp32:esp32:esp32c6 EvilAppleJuice-ESP32-INO -v
arduino-cli monitor -c baudrate=115200 -p COM4
```

Replace `COM4` with the port the ESP32 is on, and `esp32c6` with the appropriate board.

### Spamming a specific device

Some basic instructions are here: https://github.com/ckcr4lyf/EvilAppleJuice-ESP32/issues/42#issuecomment-2294610072 , but if you're not a script kiddie you can probably figure it out.
