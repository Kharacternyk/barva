from ctypes import byref
from ctypes import c_float
from ctypes import c_int
from ctypes import c_uint32
from ctypes import c_uint8
from ctypes import c_void_p
from ctypes import CDLL
from ctypes import sizeof
from ctypes import Structure
from os import getenv
from subprocess import run

from barva.source import Source


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


LIB = CDLL(getenv("BARVA_PULSE_SIMPLE", "libpulse-simple.so.0"))
LIB.pa_simple_new.restype = pa_simple_t
PA_STREAM_RECORD = 2
PA_SAMPLE_FLOAT32LE = 5


class PulseAudioSource(Source):
    def __enter__(self):
        pactl = run(["pactl", "list", "short", "sinks"], capture_output=True)
        sinks = [sink.split() for sink in pactl.stdout.splitlines()]
        active_sinks = [sink for sink in sinks if sink[-1] == b"RUNNING"]
        if active_sinks:
            sink = active_sinks[0]
        else:
            sink = sinks[0]
        source = sink[1] + b".monitor"
        sample_rate = int(sink[-2][:-2])

        self.error = c_int(0)
        self.chunk_size = int(sample_rate * self.sampling_requirements.window_size)
        sample_spec = pa_sample_spec_t(
            PA_SAMPLE_FLOAT32LE, sample_rate, self.sampling_requirements.channels
        )
        buffer_attr = pa_buffer_attr_t(-1, 0, 0, 0, self.chunk_size)
        self.pa_simple = LIB.pa_simple_new(
            None,
            b"barva",
            PA_STREAM_RECORD,
            source,
            b"barva",
            byref(sample_spec),
            None,
            byref(buffer_attr),
            byref(self.error),
        )
        return self

    def __exit__(self, etype, evalue, etrace):
        LIB.pa_simple_free(self.pa_simple)

    def __next__(self):
        samples = (c_float * self.chunk_size)()
        LIB.pa_simple_read(self.pa_simple, samples, sizeof(samples), byref(self.error))
        return samples
