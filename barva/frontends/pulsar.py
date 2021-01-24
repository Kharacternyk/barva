from collections import deque
from math import log

from backend import Backend

INERTIA = 0.9999
EPSILON = 1e-6


def weighted_root_mean_square(seq):
    sum_ = 0
    weight = (1 - INERTIA) / (1 - INERTIA ** len(seq))
    for x in seq:
        sum_ += x * x * weight
        weight *= INERTIA
    return sum_ ** (1 / 2)


def change_bg(value):
    switchfg = f"\x1b[38;2;{round(value*255)};0;0m"
    blocks = "████"
    switchnull = "\x1b[0m"
    print(switchfg + blocks + switchnull)


def pulsar(fps: float = 30):
    backend = Backend(1 / fps)

    length = int(log(EPSILON) / log(INERTIA))
    queue = deque((0,) * length, maxlen=length)
    for samples in backend:
        queue.extendleft(samples)
        change_bg(weighted_root_mean_square(queue))
