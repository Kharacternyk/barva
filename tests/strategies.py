from hypothesis.strategies import floats
from hypothesis.strategies import tuples

channels = floats(min_value=0, max_value=1)
rgb = tuples(channels, channels, channels)
