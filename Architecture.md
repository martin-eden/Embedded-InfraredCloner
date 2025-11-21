### General architecture

That's receiver and transmitter for infrared signals from/for consumer
devices. It uses text interface via UART.

It's inside body of ATmega328 with IR receiver and IR LED.

Upper-level code uses following modules: Menu, Receiver, Emitter.
Also it uses memory to store signals.

```
Menu
Memory
Receiver Emitter
```

`Menu` provides support for commands to control `Memory`, `Receiver`
and `Emitter`.

`Memory` is RAM memory that stores signals data. It's used both by
`Receiver` and `Emitter`.

`Receiver` uses hardware IR receiver module to capture signals to
`Memory`.

`Emitter` uses hardware IR LED to emit signals from `Memory`.

### Commands

#### Menu

That's generic commands that are available for any menu:

  * `? - List commands`

    Print list of available commands.

  * `^ - Exit`

    Exit current menu instance.

#### Memory

Memory data can be loaded from Receiver.
Also it can be loaded (and stored) from text (from UART).
Also it can be loaded (and stored) from EEPROM (persistent memory on ATmega328).

  * `d - Discard data`

    Clear current data.

  * `es - Print data to outside`

    External save. Prints data in text format.

  * `el - Load data from outside`

    External load. Loads data from text format.

  * `is - Save data to internal memory`

    Internal save. Saves data to EEPROM.

  * `il - Load data from internal memory`

    Internal load. Loads data from EEPROM.

#### Receiver

Receiver starts recording data after Begin command. It stops
recording data after End command.

  * `b - Begin recording`

    Start data recording. You expect to point that IR control to
    receiver and push the button you wish to capture.

  * `e - End recording`

    Stop data recording. It's good habit to stop data recording
    before exporting or replaying data.

#### Emitter

Emitter replays data from Memory with signal modulated at 38 kHz.

  * `r - Replay data`

    Replays data from Memory.

-- Martin, 2025-11-21

