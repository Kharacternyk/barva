from barva.utils import color

def define_backlight(r, g, b):
    return color.to_hex(r, g, b).strip('#')
