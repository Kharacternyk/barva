from abc import ABC
from abc import abstractmethod

from barva.sampling import SamplingRequirements


class Visualizer(ABC):
    @abstractmethod
    def __call__(self, samples):
        ...

    @property
    @abstractmethod
    def sampling_requirements(self) -> SamplingRequirements:
        ...

    def __enter__(self):
        return self

    def __exit__(self, etype, evalue, etrace):
        pass
