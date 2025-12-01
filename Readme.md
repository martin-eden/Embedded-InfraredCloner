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

Data points capacity is **75**.
Precision depends of current implementation.
Generally writing precision **≈ 50 ㎲**, reading precision **≤ 4 ㎲**

Commands documentation is [here][Commands].


## Getting started

* Receiver - `pin 8`
* Emitter - `pin 6`
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
