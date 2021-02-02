from abc import ABC
from abc import abstractmethod

from sampling import SamplingRequirements


class Frontend(ABC):
    @abstractmethod
    def __call__(self, samples):
        ...

    @property
    @abstractmethod
    def sampling_requirements(self) -> SamplingRequirements:
        ...

    def exit(self):
        pass

    def __enter__(self):
        return self

    def __exit__(self, etype, evalue, etrace):
        self.exit()
