#!/usr/bin/env python
from cli import cli
from visualizers.bars import BarsRawVisualizer
from visualizers.bars import BarsTerminalVisualizer
from visualizers.pulse import PulseBspwmBordersVisualizer
from visualizers.pulse import PulseRawVisualizer
from visualizers.pulse import PulseTerminalFireVisualizer
from visualizers.pulse import PulseTerminalsVisualizer
from visualizers.pulse import PulseTerminalVisualizer

cmds = {
    "fire": PulseTerminalFireVisualizer,
    "pulse-raw": PulseRawVisualizer,
    "pulse-term": PulseTerminalVisualizer,
    "pulse-terms": PulseTerminalsVisualizer,
    "pulse-bspwm": PulseBspwmBordersVisualizer,
    "bars-raw": BarsRawVisualizer,
    "bars": BarsTerminalVisualizer,
}


def main():
    cli(cmds)


if __name__ == "__main__":
    main()
