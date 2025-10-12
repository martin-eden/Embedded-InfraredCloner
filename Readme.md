## What

(2021/2025..)

Record and play infrared signal.

![Interface][Image_Mind]
![Body][Image_Body]


## Requirements

  * Hardware

    * Arduino Uno (ATmega328/P)
    * Generic infrared receiver
    * Generic infrared emitter

  * Software

    * If you just want to upload compiled code -- run `Upload.sh` from [`bin/`][bin]
    * [GetLibs][GetLibs]
    * [Craft][Craft]


## Notes/details

This is C++ program for ATmega328/P (Arduino Uno).

It allows you to

  [x] Capture signal from infrared receiver
  [x] Play captured signal on infrared emitter
  [x] Store/load signal in permanent memory (EEPROM)
  [x] Print signal in text format

It is designed to capture infrared signal from consumer emitters,
not to replace oscilloscope.

Duration **precision is 4** micro-seconds, data points **capacity is 80**.


## Getting started

To try, connect IR receiver to pin 8, IR emitter to pin 6 and
run code upload script in `bin/Upload.sh`. Connect to serial port
at 115200 baud.

To modify, use `GetLibs` to get framework libraries and compile program.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[bin]: bin/

[Craft]: InfraredCloner.ino
[Image_Body]: Pictures/Infrared%20cloner%20body.jpg
[Image_Mind]: Pictures/Infrared%20cloner%20mind.png

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
