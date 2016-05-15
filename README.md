# KWatch

**KWatch** is an open source, hackable smartwatch project. Currently, it's in
early development phase. This repo contains only firmware. I'll create other one
with hardware things (schematics, etc). 

### Why another smartwatch project?
I study Computer Science at the Warsaw University of Technology, [faculty of
Electronics and Information Technology](http://www.elka.pw.edu.pl/eng). This
project is my Engineering Thesis, that I have to finish before February 2017.

In fact, the idea was born in March 2015. The prices of today's devices are too
high for many people. I wanted to make smartwartch that will be affordable for
everyone.

### What parts should I buy to make my own device?
For now, essential parts for this project are:
 - (~1,5 €) STM32F1-series MCU (I use cheap Chinese STM32F103C8T6TR mini dev board)
 - (~4 €) RF-BM-S02 bluetooth low energy module
 - (~3 €) SSD1306 I2C OLED LCD (But I'm waiting for SPI TFT 128x128 color LCD)
 - (~4 €) battery (?)
 - battery charging uC (?)
 - few tact switches and other small electronic parts
 - (free) circuit board (Polish instructions [here](http://www.forbot.pl/forum/topics23/jak-zamowic-darmowe-plytki-drukowane-z-chin-podejscie-drugie-vt12383.htm))
 - ST-LINK debugger and programmer (used only once for programming MCU, so you
   can borrow it from someone to cut the cost)

### Why isn't it completed yet?
Because I'm not very experienced in embedded programming. Code can be a little
bit messy, so every advice would be appreciated!

### What software do I need to make this project?
IDE used in this project is [System Workbench for STM32](http://www.openstm32.org/System+Workbench+for+STM32).
It contains all tools you need to compile firmware and program MCU.

### Where can I find documentation?
On project's wiki. It's not filled for now but I'll put more information there
as soon as I will be confident about structure of the project.
