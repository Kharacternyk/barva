from abc import ABC
from abc import abstractmethod

from backend import Backend


class Frontend(ABC):
    def __call__(self, backend=Backend):
        try:
            for samples in Backend(self.window_size):
                result = self.next(samples)
                if result:
                    print(result)
        except KeyboardInterrupt:
            print()

    @abstractmethod
    def next(self, samples):
        ...
