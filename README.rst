.. image:: example.gif

``barva`` is an audio visualizer that pulses the background of your terminal.
``barva`` can also stream the color so that it is used to pulse something else
(see `Scripts`_ and `Arduino`_ for some examples).

.. contents:: Navigation:
   :backlinks: none

============
Installation
============

---
AUR
---

``barva-git`` `is available in AUR <https://aur.archlinux.org/packages/barva-git/>`_.
You can use AUR only if you run an Arch-based distribution. You have to install manually
otherwise, see the section below.

------
Manual
------

``barva`` depends on PulseAudio and its headers:

* On Debian (Ubuntu, Mint, …) you need ``pulseaudio`` and ``libpulse-dev`` packages.
* On Fedora (CentOS, …) you need ``pulseaudio`` and ``pulseaudio-libs-devel`` packages.
* On Arch (Manjaro, …) you need just ``pulseaudio`` package.

.. code-block:: bash

    git clone https://github.com/Kharacternyk/barva
    cd barva/src/
    CFLAGS=-O2 make

The binary is named ``barva``. You can move it to somewhere in your ``$PATH``.

=====
Usage
=====

You need to tell ``barva`` which PulseAudio source to listen to.  It's done via the
``BARVA_SOURCE`` environmental variable. The common choice is the monitor of the default
audio sink. If that's what you want, then:

* If you have built ``barva`` manually, ``cd`` into the repository and run
  ``export BARVA_SOURCE=$(./scripts/pa-get-default-monitor.sh)``.
* If you have got ``barva`` from AUR, run
  ``export BARVA_SOURCE=$(/usr/share/barva/pa-get-default-monitor.sh)``.

Then run ``barva`` while listening to some music. The background of
the terminal should turn black and pulse towards white. Press ``Ctrl+C`` to exit.

``barva`` can be a background process: run ``barva &`` and switch to another CLI program
e.g Vim. To terminate ``barva`` run ``killall barva``.

=============
Customization
=============

Customization is done via environmental variables (no CLI yet):

+-------------------------+-------------------------+-------------------------------+
| Variable                | Default value           | Description                   |
+=========================+=========================+===============================+
| ``BARVA_SOURCE``        | ``NULL``                | The PulseAudio source from    |
|                         |                         | which the audio data is read  |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_BG``            | ``#000000``             | The background color of the   |
|                         |                         | terminal                      |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_TARGET``        | ``#FFFFFF``             | The color "towards which" the |
|                         |                         | background pulses             |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_FPS``           | ``30``                  | The number of times the       |
|                         |                         | background is updated per sec |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_FORMAT`` or     | ``TTY`` if ``stdout`` is| The output format             |
| ``BARVA_OUTPUT_FORMAT`` | a tty, ``HEX`` otherwise|                               |
|                         |                         | * ``TTY``: change the         |
|                         |                         |   background of the terminal  |
|                         |                         | * ``HEX``: output the color in|
|                         |                         |   hex followed by a line feed |
|                         |                         | * ``BYT``: output the raw     |
|                         |                         |   value in range [0-255]      |
|                         |                         |   (ignores ``BARVA_BG`` and   |
|                         |                         |   ``BARVA_TARGET``)           |
+-------------------------+-------------------------+-------------------------------+

=======
Scripts
=======

All scripts in ``scripts/`` except ``pa-get-default-monitor.sh`` expect the output of
``barva`` to be piped into them e.g ``barva | bspwm-borders.sh``.  If you have got
``barva`` from AUR, the scripts are located in ``/usr/share/barva/``.

* ``to-all-ttys.sh``: pulses the backgrounds of all terminals found in ``/dev/pts/``.
  Consider using this script instead of running multiple ``barva`` instances.

* ``bspwm-borders.sh``: pulses the borders of unfocused windows under BSPWM.

=======
Arduino
=======

``barva`` can stream raw bytes that are easy to process on an Arduino board. This could
be used for some fancy hardware setups, such as a LED ribbon that pulses.

Assuming that you have set up a serial tty for your Arduino
(see `Arch Wiki <https://wiki.archlinux.org/index.php/Arduino#stty>`_),
you can just redirect ``barva``'s ``stdout`` to the tty:

.. code-block:: bash

    BARVA_FORMAT=BYT barva > /dev/ttyACM0

(replace ``/dev/ttyACM0`` with the name of the tty if it's different).

Then read the values using ``Serial.read()`` on the Arduino side. Don't forget to
setup the serial connection via ``Serial.begin()`` and check for presence of the values
via ``Serial.available()``.

See ``arduino/barva.ino`` for an example sketch. It puts high voltage on a number of
pins that depends on the value provided by ``barva``. Another possibility is to control
a PWMable pin by setting the PWM frequency according to the value provided by ``barva``.

===============
Tips and tricks
===============

----------
Compositor
----------

If you use "raw" Xorg without a DE, consider running a compositor like ``picom`` or
``compton``. It eliminates tearing and makes the pulsing smoother.

---
FPS
---

You could try bumping FPS to improve visual appearance. Beware of the possible audio
quality drop.

-----
Pywal
-----

Pywal generates a nice shell script that you could use to set the colors used by
``barva``

.. code-block:: bash

    source ~/.cache/wal/colors.sh  
    export BARVA_BG=$background BARVA_TARGET=$foreground
    barva &

---
Vim
---

Use a colorscheme that doesn't change the default terminal background color e.g
``peachpuff`` to let ``barva`` pulse the background of Vim. ``termguicolors``
(NeoVim) must be off, too.
