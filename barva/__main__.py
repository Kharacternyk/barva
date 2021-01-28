#!/usr/bin/env python
from fire import Fire
from frontends.pulse import PulseRawFrontend
from frontends.pulse import PulseTerminalFrontend
from frontends.pulse import PulseTerminalsFrontend


class CLI:
    class pulse:
        raw = PulseRawFrontend
        term = PulseTerminalFrontend
        terms = PulseTerminalsFrontend


def main():
    Fire(CLI)


if __name__ == "__main__":
    main()
