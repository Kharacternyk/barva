from abc import ABC
from abc import abstractmethod


class Frontend(ABC):
    @abstractmethod
    def __iter__(self):
        ...

    def __enter__(self):
        return self

    def __exit__(self, etype, evalue, etrace):
        pass
