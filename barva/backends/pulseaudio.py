from ctypes import byref
from ctypes import c_float
from ctypes import c_int
from ctypes import c_uint32
from ctypes import c_uint8
from ctypes import c_void_p
from ctypes import CDLL
from ctypes import sizeof
from ctypes import Structure

PA_STREAM_RECORD = 2
PA_SAMPLE_FLOAT32LE = 5


class pa_buffer_attr_t(Structure):
    _fields_ = [
        ("maxlength", c_uint32),
        ("tlength", c_uint32),
        ("prebuf", c_uint32),
        ("minreq", c_uint32),
        ("fragsize", c_uint32),
    ]


class pa_sample_spec_t(Structure):
    _fields_ = [
        ("format", c_int),
        ("rate", c_uint32),
        ("channels", c_uint8),
    ]


class pa_simple_t(c_void_p):
    pass


class Backend:
    def __init__(
        self, sample_rate=44100, refresh_ratio=24, *, lib_path="libpulse-simple.so.0"
    ):
        self._lib = CDLL(lib_path)
        self._lib.pa_simple_new.restype = pa_simple_t
        self._error = c_int(0)
        self._chunk_size = int(sample_rate / refresh_ratio)

        sample_spec = pa_sample_spec_t(PA_SAMPLE_FLOAT32LE, sample_rate, 1)
        buffer_attr = pa_buffer_attr_t(-1, 0, 0, 0, self._chunk_size)
        self._pa_simple = self._lib.pa_simple_new(
            None,
            b"barva",
            PA_STREAM_RECORD,
            b"alsa_output.pci-0000_01_00.0.analog-stereo.monitor",
            b"barva",
            byref(sample_spec),
            None,
            byref(buffer_attr),
            byref(self._error),
        )

    def __iter__(self):
        while True:
            samples = (c_float * self._chunk_size)()
            self._lib.pa_simple_read(
                self._pa_simple, samples, sizeof(samples), byref(self._error)
            )
            for s in samples:
                yield s
