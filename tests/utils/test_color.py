from hypothesis import given
from strategies import rgb

from barva.utils.color import from_hex
from barva.utils.color import to_hex


@given(rgb)
def test_to_hex_within_000000_FFFFFF(rgb):
    s = to_hex(*rgb)
    assert s >= "#000000" and s <= "#FFFFFF"


def test_from_hex():
    assert from_hex("#FFFFFF") == (1, 1, 1)
    assert from_hex("ffffff") == (1, 1, 1)
    assert from_hex("#000000") == (0, 0, 0)
    assert from_hex("ff0000") == (1, 0, 0)
