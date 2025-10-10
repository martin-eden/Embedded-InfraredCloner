## What

(2021/2025..)

Record and play infrared signal.

![Body][Image_Body]
![Interface][Image_Mind]


## Requirements

  * Hardware

    * Arduino Uno (ATmega328/P)
    * Generic infrared receiver
    * Generic infrared emitter

  * Software

    * If you just want to upload compiled code run `Upload.sh` in [`bin/`][bin]
    * [GetLibs][GetLibs]
    * [Craft][Craft]


## Notes/details

This is C++ program for ATmega328/P (Arduino Uno). It allows you to
capture signal from infrared receiver. It allows you to play captured
signal. And print it.

It is designed to capture infrared signal from consumer emitters,
not to replace oscilloscope.

Duration precision is 4 micro-seconds, data points capacity is 80.

To try, connect receiver to pin 8, emitter to pin 5 and upload code
in hex file in `bin/`. Connect to serial port at 115200 baud.

To modify, use `GetLibs` to get framework libraries and compile
sketch.


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
