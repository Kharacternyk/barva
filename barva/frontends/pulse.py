from collections import deque

from frontend import Frontend
from numpy import array
from numpy import average
from numpy import geomspace
from numpy import mean
from numpy import sqrt
from sampling import SamplingRequirements
from utils import color
from utils import term


class PulseRawFrontend(Frontend):
    """Return a color in hex that pulses."""

    def __init__(
        self,
        *,
        fps: float = 30,
        cfrom: str = "#000000",
        cto: str = "#FF0000",
        inertia: float = 1.5,
    ):
        """
        fps: the number of times the color is updated per second
        cfrom: pulse "from" this color
        cto: pulse "to" this color
        inertia: the timespan over which the color fades in case of silence
        """
        self.fps = fps
        self.cfrom = color.from_hex(cfrom)
        self.cto = color.from_hex(cto)
        self.length = int(inertia * fps)
        self.weights = geomspace(1, 1e-3, self.length)
        self.queue = deque((0,) * self.length, maxlen=self.length)

    @property
    def sampling_requirements(self):
        return SamplingRequirements(
            channels=1,
            window_size=1 / self.fps,
        )

    def __call__(self, samples):
        self.queue.appendleft(mean(array(samples) ** 2))
        value = sqrt(average(self.queue, weights=self.weights))
        r, g, b = (c1 + (c2 - c1) * value for c1, c2 in zip(self.cfrom, self.cto))
        return color.to_hex(r, g, b)


class PulseTerminalFrontend(PulseRawFrontend):
    """Pulse this terminal."""

    def __call__(self, samples):
        print(term.change_bg(super().__call__(samples)), end="", flush=True)

    def exit(self):
        print(term.change_bg(color.to_hex(*self.cfrom)))


class PulseTerminalsFrontend(PulseRawFrontend):
    """Pulse all terminals."""

    def __call__(self, samples):
        term.to_all(term.change_bg(super().__call__(samples)))

    def exit(self):
        term.to_all(term.change_bg(color.to_hex(*self.cfrom)))
