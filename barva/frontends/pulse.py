from collections import deque

from frontend import Frontend
from numpy import array
from numpy import average
from numpy import geomspace
from numpy import mean
from numpy import sqrt
from utils import color


class pulse(Frontend):
    def __init__(
        self,
        fps: float = 30,
        bg: str = "#000000",
        target="#FF0000",
        inertia: float = 1.5,
        epsilon: float = 1e-3,
    ):
        self.window_size = 1 / fps
        self.bg = color.from_hex(bg)
        self.target = color.from_hex(target)
        length = int(fps * inertia)
        self.weights = geomspace(1, epsilon, length)
        self.queue = deque((0,) * length, maxlen=length)

    def next(self, samples):
        self.queue.appendleft(sqrt(mean(array(samples) ** 2)))
        value = average(self.queue, weights=self.weights)
        r, g, b = (c1 + (c2 - c1) * value for c1, c2 in zip(self.bg, self.target))
        print(f"\033]11;{color.to_hex(r, g, b)}\007", end="", flush=True)

    def end(self):
        return f"\033]11;{color.to_hex(*self.bg)}\007"
