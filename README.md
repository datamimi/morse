### Morse Key USB Keyboard

#### What's this?

This repo contains code to convert a physical Morse key into a USB keyboard, via
a Teensy 3.2. This means you can plug the Morse key into any laptop or computer and use it in exactly the same way as a conventional keyboard, except you type in Morse and the characters appear on screen in English.

The keyboard currently supports lowercase letters of the alphabet from a-z and numbers 0-9.

Unrecognised characters are printed out as a dash, or "-".

Timings between characters and words are currently hardcoded in ms. This isn't hugely accurate since different operators will key at different speeds, but the hardcoded timings can easily be tweaked.

#### What do I need to replicate this?

You'll need a Teensy 3.2 and a physical Morse key. I've configured my Teensy so one output from the Morse key is connected to Pin 7, and the other is connected to a ground pin.
