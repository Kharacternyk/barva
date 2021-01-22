from ctypes import byref
from ctypes import c_float
from ctypes import c_int
from ctypes import c_uint32
from ctypes import c_uint8
from ctypes import c_void_p
from ctypes import CDLL
from ctypes import sizeof
from ctypes import Structure
from subprocess import run


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


class PulseAudioBackend:
    def __init__(self, window_size, *, lib_path="libpulse-simple.so.0"):
        PA_STREAM_RECORD = 2
        PA_SAMPLE_FLOAT32LE = 5

        self._lib = CDLL(lib_path)
        self._lib.pa_simple_new.restype = pa_simple_t
        self._error = c_int(0)

        pactl = run(["pactl", "list", "short", "sinks"], capture_output=True)
        sinks = [sink.split() for sink in pactl.stdout.splitlines()]
        active_sinks = [sink for sink in sinks if sink[-1] == b"RUNNING"]
        if active_sinks:
            sink = active_sinks[0]
        else:
            sink = sinks[0]

        source = sink[1] + b".monitor"
        sample_rate = int(sink[-2][:-2])

        self._chunk_size = int(sample_rate * window_size)

        sample_spec = pa_sample_spec_t(PA_SAMPLE_FLOAT32LE, sample_rate, 1)
        buffer_attr = pa_buffer_attr_t(-1, 0, 0, 0, self._chunk_size)
        self._pa_simple = self._lib.pa_simple_new(
            None,
            b"barva",
            PA_STREAM_RECORD,
            source,
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
            yield samples
