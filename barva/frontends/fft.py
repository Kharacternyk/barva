import numpy
from backend import Backend


def fft(n: int = 5, window_size: float = 0.05):
    """Print results of the one-dimensional n-point DFT to stdout.

    Args:
        n: The n-point DFT will be computed.
    """

    backend = Backend(window_size)
    for samples in backend:
        print(" ".join(f"{s:.4f}" for s in abs(numpy.fft.fft(samples, n))))
