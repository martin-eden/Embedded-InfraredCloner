## What

(2025-09/2025-11, 2026-03-26)

Records and plays infrared signal. Scriptable interface.

![Interface][Image_Mind]
![Body][Image_Body]


## Notes/details

This is C++ program for ATmega328/P (Arduino Uno) designed to capture
infrared signal from consumer emitters.

It allows you to

  - [x] Capture signal from infrared receiver
  - [x] Play captured signal on infrared emitter
  - [x] Store/load signal in text format
  - [x] Store/load signal in permanent memory (EEPROM)

Data points capacity: **100**
Emitting frequency: **38 kHz**
Reading precision: **≤ 4 ㎲**
Writing precision: **≤ 20 ㎲**

Commands described [here][Commands].


## Getting started

  Hardware requirements

    * Arduino Uno (ATmega328/P)
    * Generic infrared emitter
    * Generic infrared receiver

  Wiring

    * Emitter - `pin 5`
    * Receiver - `pin 8`

  Software requirements

    * Compiled binary [`bin/InfraredClonerino.hex`][Hex]

    Upload binary to Uno board. We have [`bin/Upload.sh`][Upload.sh]
    script just for that. (Requires `bash` and `avrdude`.)

  Connect at `115200 baud`. There will be text menu.


## Recompiling

Use [`GetLibs`][GetLibs] to get framework libraries and compile program.

(Requires `bash` and `arduino-cli`.)

Program compiled with most recent code may not work properly.
That's life, not everything is always perfect.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Hex]: bin/InfraredCloner.ino.hex

[Upload.sh]: bin/Upload.sh

[Craft]: InfraredCloner.ino
[Image_Body]: Pictures/Infrared%20cloner%20body.jpg
[Image_Mind]: Pictures/Infrared%20cloner%20mind.png

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Commands]: Architecture.md

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
