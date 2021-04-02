#!/usr/bin/env python
from barva.cli import cli
from barva.visualizers.pulse import PulseBspwmBordersVisualizer
from barva.visualizers.pulse import PulseHexVisualizer
from barva.visualizers.pulse import PulseTerminalFireVisualizer
from barva.visualizers.pulse import PulseTerminalsVisualizer
from barva.visualizers.pulse import PulseTerminalVisualizer

cmds = {
    "pulse-fire": PulseTerminalFireVisualizer,
    "pulse-hex": PulseHexVisualizer,
    "pulse-term": PulseTerminalVisualizer,
    "pulse-terms": PulseTerminalsVisualizer,
    "pulse-bspwm": PulseBspwmBordersVisualizer,
}


def main():
    cli(cmds)


if __name__ == "__main__":
    main()
