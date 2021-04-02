Barva is a modular audio visualizer, which aims to be cross-platform and implement multiple
frontends, e.g. bars, pulse, milkdrop-like.

As of now, only GNU/Linux (PulseAudio) is supported. The "pulse" frontend is implemented and the "bars" one is being developed. Despite being unfinished, this version of Barva has already superseded the functionality of the old Barva, which is written in C and lives in `the legacy branch`_.

**IMPORTANT:** The "pulse" frontend can, in theory, harm people sensitive to flashing.
Please, don't use it if you have such condition.

============
Installation
============

``pip install barva``

=====
Usage
=====

.. code-block::

  $ barva --help
  usage: barva [-h] visualizer ...

  positional arguments:
    visualizer
      pulse-fire
                 Draw a fire-like animation.
      pulse-hex  Yield a hex color that pulses.
      pulse-term
                 Pulse this terminal.
      pulse-terms
                 Pulse all terminals.
      pulse-bspwm
                 Pulse the window borders (requires BSPWM).

  optional arguments:
    -h, --help   show this help message and exit

Each subcommand also has its own help message, e.g. ``barva pulse-fire --help``.

If Barva doesn't seem to work, it's likely that it hasn't guessed which audio sink to
monitor correctly. In this case, make sure that some music is already being played
through the right speakers/headphones when you start Barva.

.. _the legacy branch: https://github.com/Kharacternyk/barva/tree/legacy
