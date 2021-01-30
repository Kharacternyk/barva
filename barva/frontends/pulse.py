from collections import deque

from frontend import Frontend
from numpy import array
from numpy import average
from numpy import geomspace
from numpy import mean
from numpy import sqrt
from utils import color
from utils import term


class PulseRawFrontend(Frontend):
    """Yield a color in hex that pulses."""

    def __init__(
        self,
        *,
        fps: float = 30,
        cfrom: str = "#000000",
        cto: str = "#FF0000",
        inertia: float = 1.5,
    ):
        """
        Args:
            fps: the number of times the color is updated per second
            cfrom: pulse "from" this color
            cto: pulse "to" this color
            inertia: the timespan over which the color fades in case of silence
        """
        self.window_size = 1 / fps
        self.cfrom = color.from_hex(cfrom)
        self.cto = color.from_hex(cto)
        length = int(fps * inertia)
        self.weights = geomspace(1, 1e-3, length)
        self.queue = deque((0,) * length, maxlen=length)

    def next(self, samples):
        self.queue.appendleft(mean(array(samples) ** 2))
        value = sqrt(average(self.queue, weights=self.weights))
        r, g, b = (c1 + (c2 - c1) * value for c1, c2 in zip(self.cfrom, self.cto))
        return color.to_hex(r, g, b)


class PulseTerminalFrontend(PulseRawFrontend):
    """Pulse this terminal."""

    def next(self, samples):
        print(term.change_bg(super().next(samples)), end="", flush=True)

    def end(self):
        print(term.change_bg(color.to_hex(*self.cfrom)))


class PulseTerminalsFrontend(PulseRawFrontend):
    """Pulse all terminals."""

    def next(self, samples):
        term.to_all(term.change_bg(super().next(samples)))

    def end(self):
        term.to_all(term.change_bg(color.to_hex(*self.cfrom)))
