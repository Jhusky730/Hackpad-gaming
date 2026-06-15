# my_hackpad

![my_hackpad](https://imgur.com/replace_me.png)

A fully custom 9-key mechanical macropad featuring an orthilinear 3x3 layout, an SSD1306 OLED screen, a rotary encoder, and an addressable per-key SK6812MINI-E RGB matrix. It is pre-configured with a daily desktop utility layer and a dedicated tactical combat deck for EVE Online.

* Keyboard Maintainer: [Jack Huskinson](https://github.com/Jhusky730)
* Hardware Supported: Custom 3x3 PCB, Seeed Studio XIAO RP2040 Controller
* Hardware Availability: Open-source PCB files / Self-sourced components

## Compiling the Firmware

To compile the default layout for this keyboard, run the following command in your QMK CLI environment:

    qmk compile -kb my_hackpad -km default

## Flashing the Microcontroller

Since the Seeed Studio XIAO RP2040 uses a UF2 bootloader, you can flash it using the standard drag-and-drop method:

1. Compile the firmware using the command above to generate the `.uf2` file.
2. Put the keyboard into **Bootloader mode** (see instructions below).
3. A mass storage drive named `RPI-RP2` will appear on your computer.
4. Drag and drop the compiled `my_hackpad_default.uf2` file directly onto that drive. The board will automatically flash and reboot.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Because your board uses a modern RP2040 processor, you can enter the bootloader in 2 reliable hardware ways:

* **Physical Button Combination**: Hold down the **B** (Boot) button on the underside of the XIAO RP2040 module, press and release the **R** (Reset) button, and then release the Boot button.
* **Physical Pads**: If your custom PCB exposes them, briefly short the two `RST` pads together while the device is plugged in.