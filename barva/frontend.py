from abc import ABC
from abc import abstractmethod

from backend import Backend


class Frontend(ABC):
    def __call__(self, backend=Backend):
        for samples in Backend(self.window_size):
            result = self.next(samples)
            if result:
                yield result

    @abstractmethod
    def next(self, samples):
        ...
