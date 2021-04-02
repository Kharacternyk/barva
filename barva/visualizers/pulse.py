import socket
from collections import deque
from glob import glob
from os import access
from os import getenv
from os import scandir
from os import W_OK
from shutil import get_terminal_size

from numpy import array
from numpy import average
from numpy import geomspace
from numpy import mean
from numpy import sqrt

from barva.sampling import SamplingRequirements
from barva.utils import color
from barva.utils import term
from barva.visualizer import Visualizer


class PulseRawVisualizer(Visualizer):
    """Yield (r, g, b) tuples of a color that pulses."""

    def __init__(
        self,
        *,
        fps: float = 30,
        cfrom: str = "#000000",
        cto: str = "#00FFFF",
        inertia: float = 1.5,
        unsafe: bool = False,
    ):
        """
        fps: the number of times the color is updated per second
        cfrom: pulse "from" this color
        cto: pulse "to" this color
        inertia: the timespan in seconds over which the color fades in case of silence
        unsafe: whether to allow inertia values less than 1.5s
        """
        if not unsafe and inertia < 1.5:
            raise ValueError(
                "Inertia values lower than 1.5s are forbidden to prevent potentially"
                + " harmful flashing.\n"
                + "Pass `--unsafe true' if you want to override this."
            )
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
        return (r, g, b)


class PulseHexVisualizer(PulseRawVisualizer):
    """Yield a hex color that pulses."""

    def __call__(self, samples):
        return color.to_hex(*super().__call__(samples))


class PulseTerminalVisualizer(PulseRawVisualizer):
    """Pulse this terminal."""

    def __call__(self, samples):
        print(term.define_bg(*super().__call__(samples)), end="", flush=True)

    def __exit__(self, etype, evalue, etrace):
        print(term.define_bg(*self.cfrom), end="", flush=True)


class PulseTerminalsVisualizer(PulseRawVisualizer):
    """Pulse all terminals."""

    @staticmethod
    def to_all_terms(msg):
        for entry in scandir("/dev/pts"):
            if access(entry.path, W_OK):
                with open(entry.path, "w") as file:
                    print(msg, file=file, end="", flush=True)

    def __call__(self, samples):
        self.to_all_terms(term.define_bg(*super().__call__(samples)))

    def __exit__(self, etype, evalue, etrace):
        self.to_all_terms(term.define_bg(*self.cfrom))


class PulseTerminalFireVisualizer(PulseRawVisualizer):
    """Draw a fire-like animation."""

    def __enter__(self):
        columns, rows = get_terminal_size()
        print(term.switch_bg(*self.cfrom))
        print(" " * columns * rows)
        print(term.hide_cursor)
        return self

    def __call__(self, samples):
        columns, _ = get_terminal_size()
        print(term.switch_bg(*super().__call__(samples)) + " " * columns)

    def __exit__(self, etype, evalue, etrace):
        print(term.show_cursor + term.reset_colors + term.clear_screen, end="")


class PulseBspwmBordersVisualizer(PulseHexVisualizer):
    """Pulse the window borders (requires BSPWM)."""

    def __enter__(self):
        self.socket_file = getenv("BSPWM_SOCKET", None)
        if not self.socket_file:
            possible_sockets = glob("/tmp/bspwm*_*_*-socket")
            if not possible_sockets:
                raise ValueError("No BSPWM socket found")
            if len(possible_sockets) > 1:
                raise ValueError(
                    f"Could not choose the right BSPWM socket among {possible_sockets}"
                )
            self.socket_file = possible_sockets[0]
        return self

    def __call__(self, samples):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.connect(self.socket_file)
        s.send(
            b"config\x00normal_border_color\x00"
            + f"{super().__call__(samples)}\x00".encode()
        )
        s.close()

    def __exit__(self, etype, evalue, etrace):
        # TODO We could get the previously used border color from bspc and restore it.
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.connect(self.socket_file)
        s.send(
            b"config\x00normal_border_color\x00"
            + f"{color.to_hex(*self.cfrom)}\x00".encode()
        )
        s.close()
