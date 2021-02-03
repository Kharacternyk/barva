import curses

from numpy.fft import fft
from sampling import SamplingRequirements
from visualizer import Visualizer


class FftRawVisualizer(Visualizer):
    """Return results of the Discrete Fourier Transform."""

    def __init__(
        self,
        *,
        count: int = 5,
        fps: float = 30,
    ):
        """
        count: the number of points over which the DFT is computed
        fps: the number of times the DFT is computed per second
        """
        self.count = count
        self.fps = fps

    @property
    def sampling_requirements(self):
        return SamplingRequirements(
            channels=1,
            window_size=1 / self.fps,
        )

    def __call__(self, samples):
        return abs(fft(samples, self.count)) / self.count


class FftBarsVisualizer(FftRawVisualizer):
    """Draw bars representing the DFT in an ncurses window."""

    def __enter__(self):
        self.screen = curses.initscr()
        curses.cbreak()
        return self

    def __call__(self, samples):
        self.screen.erase()
        for col, height in zip(range(self.count), super().__call__(samples)):
            height = int(height * (curses.LINES - 1))
            if height:
                self.screen.move(curses.LINES - height, col)
                self.screen.vline(curses.ACS_BOARD, height)
        self.screen.refresh()

    def __exit__(self, etype, evalue, etrace):
        curses.nocbreak()
        curses.echo()
        curses.endwin()
