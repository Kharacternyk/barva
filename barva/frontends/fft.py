import numpy
from backend import Backend


def fft(n: int = 5, window_size: float = 0.05):
    """Yield results of the one-dimensional n-point DFT.

    Args:
        n: The n-point DFT will be computed.
        window_size: The timespan over which the DFT is computed.
    """

    return (
        " ".join(f"{s:.4f}" for s in abs(numpy.fft.fft(samples, n)))
        for samples in Backend(window_size)
    )
