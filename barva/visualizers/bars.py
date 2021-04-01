import curses

from numpy import array
from numpy import array_split
from numpy import clip
from numpy import log10
from numpy.fft import fft

from barva.sampling import SamplingRequirements
from barva.visualizer import Visualizer


class BarsRawVisualizer(Visualizer):
    """Return numbers in range [0; 1] representing the audio spectrum."""

    def __init__(self, *, count: int = 40, fps: float = 30, acceleration: float = 1):
        """
        count: the number of bars
        fps: the number of times bars are updated
        acceleration: the acceleration of falling bars in (max-bar-height)/s^2
        """
        self.count = count
        self.fps = fps
        self.acceleration = acceleration
        self.velocities = array([0.0] * count)
        self.positions = None

    @property
    def sampling_requirements(self):
        return SamplingRequirements(
            channels=1,
            window_size=1 / self.fps,
        )

    def __call__(self, samples):
        freq_bins = abs(array_split(fft(samples, self.count * 2), 2)[0]) / self.count
        new_positions = clip(log10(freq_bins * 9 + 1), 0, 1)
        if self.positions is None:
            self.positions = new_positions
            return new_positions
        self.velocities += self.acceleration / self.fps
        self.positions -= self.velocities / self.fps

        for i in range(len(new_positions)):
            if new_positions[i] > self.positions[i]:
                self.velocities[i] = 0
            else:
                new_positions[i] = self.positions[i]
        self.positions = new_positions
        return new_positions


class BarsTerminalVisualizer(BarsRawVisualizer):
    """Draw bars representing the audio spectrum in an ncurses window."""

    def __enter__(self):
        self.screen = curses.initscr()
        curses.curs_set(0)
        curses.cbreak()
        return self

    def __call__(self, samples):
        self.screen.erase()
        for col, height in zip(range(self.count), super().__call__(samples)):
            height = int(height * (curses.LINES - 1))
            if height:
                self.screen.move(curses.LINES - height, col)
                self.screen.vline(curses.ACS_BLOCK, height)
        self.screen.refresh()

    def __exit__(self, etype, evalue, etrace):
        curses.nocbreak()
        curses.echo()
        curses.endwin()
