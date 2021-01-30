#!/usr/bin/env python
from cli import cli
from frontends.pulse import PulseRawFrontend
from frontends.pulse import PulseTerminalFrontend
from frontends.pulse import PulseTerminalsFrontend

cmds = {
    "pulse-raw": PulseRawFrontend,
    "pulse-term": PulseTerminalFrontend,
    "pulse-terms": PulseTerminalsFrontend,
}


def main():
    cli(cmds)


if __name__ == "__main__":
    main()
