from collections import deque
from math import log

from frontend import Frontend
from utils import color

_INERTIA = 0.9999
_EPSILON = 1e-6
_LENGTH = int(log(_EPSILON) / log(_INERTIA))


def _weighted_root_mean_square(seq):
    sum_ = 0
    weight = (1 - _INERTIA) / (1 - _INERTIA ** len(seq))
    for x in seq:
        sum_ += x * x * weight
        weight *= _INERTIA
    return sum_ ** (1 / 2)


class pulsar(Frontend):
    def __init__(self, fps: float = 30, bg: str = "#000000", target="#FF0000"):
        self.window_size = 1 / fps
        self.queue = deque((0,) * _LENGTH, maxlen=_LENGTH)
        self.bg = color.from_hex(bg)
        self.target = color.from_hex(target)

    def next(self, samples):
        self.queue.extendleft(samples)
        value = _weighted_root_mean_square(self.queue)
        r, g, b = (c1 + (c2 - c1) * value for c1, c2 in zip(self.bg, self.target))
        print(f"\033]11;{color.to_hex(r, g, b)}\007", end="", flush=True)
