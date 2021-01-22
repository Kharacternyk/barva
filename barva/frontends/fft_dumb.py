from backend import Backend
from fire.core import FireError
from numpy.fft import fft
from typeguard import check_argument_types


def fft_dumb(n: int = 5, window_size: float = 1 / 24):
    try:
        check_argument_types()
        backend = Backend(window_size)
        for samples in backend:
            print(" ".join(f"{s:.4f}" for s in abs(fft(samples, n))))
    except Exception as e:
        raise FireError(str(e))
