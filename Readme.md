## What

(2021/2025..)

Record and play infrared signal.

![Body][Image_Body]
![Interface][Image_Mind]
![Data][Image_IrData]


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

Programs are flowers of framework.. But this one shapes framework.

This one was standalone program. Then library. Then example to library.

I wanted to make code occupy less screens and `[me_Menu]` and
`[me_Console]` were created. And `[me_Counters]`.
Each one took at least couple of months work.

It lived as example in `[me_Counters]` doing some useful low-level
stuff which I recently extracted to three modules. Who's example it
is now?

It lives in a separate board in real world like Flower friend and
Pour manager, Hygrometer, Ultrasonic ruler and Willy the Rover "projects".
But this board has generic modular design, not like custom builds for them.
It has no physical buttons or screens. But it has console interface.
Which just tolerates human. Really it expects something another on that end.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[bin]: bin/

[Craft]: InfraredCloner.ino
[Image_Body]: Pictures/Infrared%20cloner%20body.jpg
[Image_Mind]: Pictures/Infrared%20cloner%20mind.png
[Image_IrData]: Pictures/IR%20data%20series.png

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
