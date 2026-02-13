## What

(2025-09/2025-11)

Record and play infrared signal. Scriptable interface.

![Interface][Image_Mind]
![Body][Image_Body]


## Requirements

  * Hardware

    * Arduino Uno (ATmega328/P)
    * Generic infrared receiver
    * Generic infrared emitter

  * Software

    * Upload compiled code:

      * `bash`
      * `avrdude`
      * Run [`Upload.sh`][Upload.sh] from `bin/`.

    * Compile code:

      * `arduino-cli`
      * [GetLibs][GetLibs]
      * [Craft][Craft]


## Notes/details

This is C++ program for ATmega328/P (Arduino Uno).

It allows you to

  - [x] Capture signal from infrared receiver
  - [x] Play captured signal on infrared emitter
  - [x] Store/load signal in text format
  - [x] Store/load signal in permanent memory (EEPROM)

It is designed to capture infrared signal from consumer emitters,
not to replace oscilloscope.

Emitting frequency: **38 kHz**
Writing precision: **≤ 20 ㎲**
Reading precision: **≤ 4 ㎲**
Data points capacity: **100**

Commands described [here][Commands].


## Getting started

* Emitter - `pin 5`
* Receiver - `pin 8`
* Run [`Upload.sh`][Upload.sh]
* Connect with `115200 baud`

To modify, use [`GetLibs`][GetLibs] to get framework libraries and compile program.

(Program compiled with current code may not work properly.
That's life, not everything is always perfect. For version that works
("worked some day when we tested it") use binary file.)


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Upload.sh]: bin/Upload.sh

[Craft]: InfraredCloner.ino
[Image_Body]: Pictures/Infrared%20cloner%20body.jpg
[Image_Mind]: Pictures/Infrared%20cloner%20mind.png

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Commands]: Architecture.md

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
