import numpy
from frontend import Frontend


class fft(Frontend):
    """Yield results of the one-dimensional n-point DFT.

    Args:
        n: The n-point DFT will be computed.
        window_size: The timespan over which the DFT is computed.
    """

    def __init__(self, n: int = 5, window_size: float = 0.05):
        self.n = n
        self.window_size = window_size

    def next(self, samples):
        return " ".join(f"{s:.4f}" for s in abs(numpy.fft.fft(samples, self.n)))
