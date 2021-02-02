#!/usr/bin/env python
from cli import cli
from visualizers.fft import FftBarsVisualizer
from visualizers.fft import FftRawVisualizer
from visualizers.pulse import PulseRawVisualizer
from visualizers.pulse import PulseTerminalsVisualizer
from visualizers.pulse import PulseTerminalVisualizer

cmds = {
    "pulse-raw": PulseRawVisualizer,
    "pulse-term": PulseTerminalVisualizer,
    "pulse-terms": PulseTerminalsVisualizer,
    "fft-raw": FftRawVisualizer,
    "fft-bars": FftBarsVisualizer,
}


def main():
    cli(cmds)


if __name__ == "__main__":
    main()
