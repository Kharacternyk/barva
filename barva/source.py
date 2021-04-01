from abc import ABC
from abc import abstractmethod

from barva.sampling import SamplingRequirements


class Source(ABC):
    @abstractmethod
    def __enter__(self):
        ...

    @abstractmethod
    def __exit__(self, etype, evalue, etrace):
        ...

    @abstractmethod
    def __next__(self):
        ...

    def __init__(self, sampling_requirements: SamplingRequirements):
        self.sampling_requirements = sampling_requirements

    def __iter__(self):
        return self
