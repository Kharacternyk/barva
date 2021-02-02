import curses

from numpy.fft import fft
from sampling import SamplingRequirements
from visualizer import Visualizer


class FftRawVisualizer(Visualizer):
    """Return results of the Discrete Fourier Transform."""

    def __init__(
        self,
        *,
        n: int = 5,
        fps: float = 30,
    ):
        """
        n: the n-point DFT is computed
        fps: the number of times the DFT is computed per second
        """
        self.n = n
        self.fps = fps

    @property
    def sampling_requirements(self):
        return SamplingRequirements(
            channels=1,
            window_size=1 / self.fps,
        )

    def __call__(self, samples):
        return abs(fft(samples, self.n)) / self.n


class FftBarsVisualizer(FftRawVisualizer):
    """Draw bars representing the DFT in an ncurses window."""

    def __enter__(self):
        self.screen = curses.initscr()
        curses.cbreak()
        return self

    def __call__(self, samples):
        self.screen.clear()
        for row, height in zip(range(self.n), super().__call__(samples)):
            self.screen.move(row, 0)
            self.screen.addstr("#" * int(height * (curses.COLS - 1)))
        self.screen.refresh()

    def __exit__(self, etype, evalue, etrace):
        curses.nocbreak()
        curses.echo()
        curses.endwin()
