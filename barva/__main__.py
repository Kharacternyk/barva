#!/usr/bin/env python
from cli import cli
from visualizers.pulse import PulseRawVisualizer
from visualizers.pulse import PulseTerminalsVisualizer
from visualizers.pulse import PulseTerminalVisualizer

cmds = {
    "pulse-raw": PulseRawVisualizer,
    "pulse-term": PulseTerminalVisualizer,
    "pulse-terms": PulseTerminalsVisualizer,
}


def main():
    cli(cmds)


if __name__ == "__main__":
    main()
