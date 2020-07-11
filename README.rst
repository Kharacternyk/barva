.. image:: example.gif

``barva`` is an audio visualizer that pulses the background of your terminal.
``barva`` can also stream the color so that it is used to pulse something else
(see `Scripts`_ for some examples).

The equalizer shown in the gif is `cava <https://github.com/karlstav/cava>`_.

.. contents:: Navigation:
   :backlinks: none

============
Installation
============

---
AUR
---

``barva-git`` `is available in AUR <https://aur.archlinux.org/packages/barva-git/>`_.

------
Manual
------

``barva`` depends on PulseAudio and its headers:

* On Debian (Ubuntu, Mint, ...) you need ``pulseaudio`` and ``libpulse-dev`` packages.
* On Fedora (CentOS, ...) you need ``pulseaudio`` and ``pulseaudio-libs-devel`` packages.
* On Arch (Manjaro, ...) you need just ``pulseaudio`` package.

Clone this repository, ``cd`` into its directory and run ``make`` (GCC is required).
The binary is named ``barva``. You can move it to somewhere in your ``$PATH``.

=====
Usage
=====

You need to specify the name of PulseAudio source from which ``barva`` should read audio.
It's done via ``BARVA_SOURCE`` environmental variable. The common case is that you want
``barva`` to monitor your default audio sink. It can be accomplished with the help of
``pa-get-default-monitor.sh``:

* If you have built ``barva`` manually, ``cd`` into the repository and run
  ``export BARVA_SOURCE=$(./scripts/pa-get-default-monitor.sh)``.
* If you have got ``barva`` from AUR, run
  ``export BARVA_SOURCE=$(/usr/share/barva/pa-get-default-monitor.sh)``.

Then run ``barva`` or ``./barva`` while listening to some music. The background of
the terminal should turn black and pulse towards white. Press ``Ctrl+C`` to exit.

You can send ``barva`` to the background and switch to another CLI program e.g Vim:
just run ``barva &``. To terminate ``barva``, run ``killall barva`` or some other equivalent.

=============
Customization
=============

Customization is done via environmental variables (no CLI yet):

+-------------------------+-------------------------+-------------------------------+
| Variable                | Default value           | Description                   |
+=========================+=========================+===============================+
| ``BARVA_SOURCE``        | ``NULL``                | The PulseAudio source from    |
|                         |                         | which audio is read           |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_BG``            | ``#000000``             | The background color of the   |
|                         |                         | terminal                      |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_TARGET``        | ``#FFFFFF``             | The color "towards which" the |
|                         |                         | background pulses             |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_FPS``           | ``60``                  | The number of times the       |
|                         |                         | background is updated per sec |
+-------------------------+-------------------------+-------------------------------+
| ``BARVA_FORMAT`` or     | ``TTY`` if ``stdout`` is| The format of output          |
| ``BARVA_OUTPUT_FORMAT`` | a tty, ``HEX`` otherwise|                               |
|                         |                         | * ``TTY``: change the         |
|                         |                         |   background of the terminal  |
|                         |                         | * ``HEX``: output the color in|
|                         |                         |   hex, one per line           |
|                         |                         | * ``BYT``: output the raw     |
|                         |                         |   value in range [0-255]      |
|                         |                         |   (ignores ``BARVA_BG`` and   |
|                         |                         |   ``BARVA_TARGET``)           |
+-------------------------+-------------------------+-------------------------------+

=======
Scripts
=======

All scripts in ``scripts/`` (except ``pa-get-default-monitor.sh``)
expect output of ``barva`` to be piped into them e.g ``barva | bspwm-borders.sh``.
If you have got ``barva`` from AUR, the scripts are located in ``/usr/share/barva/``.

--------------
to-all-ttys.sh
--------------

Pulses the backgrounds of all terminals found in ``/dev/pts/``. Consider using this
script instead of running multiple ``barva`` instances: it will save you some CPU time.

----------------
bspwm-borders.sh
----------------

Pulses the borders of not-focused windows under BSPWM.

=======
Arduino
=======

``barva``, apart from the color, can also stream the raw byte value that is easy to
process on an Arduino board. This could be used for some fancy hardware setups, such as
a LED ribbon that pulses.

Assuming that you have set up a serial tty for your Arduino
(see `Arch Wiki <https://wiki.archlinux.org/index.php/Arduino#stty>`_)
you can just redirect ``barva``'s ``stdout`` to the tty:

.. code-block:: bash

    BARVA_FORMAT=BYT barva > /dev/ttyACM0

(replace ``/dev/ttyACM0`` with the name of the tty if it's different).

Then, on the Arduino side, read the value using ``Serial.read()``. Don't forget to
setup the serial connection via ``Serial.begin()`` and check for presence of input
before reading it via ``Serial.available()``.

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
``compton``. It eliminates tearing, thus making ``barva`` smoother.

---
FPS
---

The CPU usage of ``barva`` is roughly proportional to the value of ``BARVA_FPS``.
Therefore, lowering the value is the first thing to try to improve performance
(please report such cases, ``barva`` is supposed to be reasonably fast *everywhere*).

If you have a high refresh-rate monitor, you may try making ``BARVA_FPS`` bigger:
the appearance may improve (at the cost of CPU cycles, though).

-----
Pywal
-----

Pywal generates a nice ``~/.cache/wal/colors.sh`` file that you may use to set
the colors used by ``barva``

.. code-block:: bash

    source ~/.cache/wal/colors.sh  
    export BARVA_BG=$background BARVA_TARGET=$foreground
    barva &

---
Vim
---

To let ``barva`` pulse the background of Vim, use a colorscheme that doesn't change
the default terminal background color e.g ``peachpuff``.
``termguicolors`` (NeoVim) must be off, too.
