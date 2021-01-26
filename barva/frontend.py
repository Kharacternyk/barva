from abc import ABC
from abc import abstractmethod

from backend import Backend


class Frontend(ABC):
    def __call__(self, backend=Backend):
        try:
            for samples in Backend(self.window_size):
                result = self.next(samples)
                if result is not None:
                    yield result
        except KeyboardInterrupt:
            result = self.end()
            if result is not None:
                yield result

    @abstractmethod
    def next(self, samples):
        ...

    def end(self):
        return ""
