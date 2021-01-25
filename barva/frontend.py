from abc import ABC
from abc import abstractmethod

from backend import Backend


class Frontend(ABC):
    def __call__(self, backend=Backend):
        return (self.next(samples) for samples in Backend(self.window_size))

    @abstractmethod
    def next(self):
        ...
