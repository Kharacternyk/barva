def to_hex(r, g, b):
    """Return the hexadecimal representation of a color."""
    return f"#{round(r*255):02X}{round(g*255):02X}{round(b*255):02X}"


def from_hex(s):
    """Parse the hexadecimal representation of a color."""
    s = s.lstrip("#")
    return tuple(int(s[i : i + 2], 16) / 255 for i in (0, 2, 4))
