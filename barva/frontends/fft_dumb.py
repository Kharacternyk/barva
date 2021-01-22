from backend import Backend
from numpy.fft import fft


def fft_dumb(*, n=5, window_size=1 / 24):
    backend = Backend(window_size)
    for samples in backend:
        print(" ".join(f"{s:.4f}" for s in abs(fft(samples, n))))
