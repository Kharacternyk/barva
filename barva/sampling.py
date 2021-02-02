from dataclasses import dataclass


@dataclass(frozen=True)
class SamplingRequirements:
    channels: int
    window_size: float
