#!/usr/bin/env python
from barva.cli import cli
from barva.visualizers.bars import BarsRawVisualizer
from barva.visualizers.bars import BarsTerminalVisualizer
from barva.visualizers.pulse import PulseBspwmBordersVisualizer
from barva.visualizers.pulse import PulseRawVisualizer
from barva.visualizers.pulse import PulseTerminalFireVisualizer
from barva.visualizers.pulse import PulseTerminalsVisualizer
from barva.visualizers.pulse import PulseTerminalVisualizer

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
