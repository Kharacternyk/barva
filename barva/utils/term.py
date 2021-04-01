from barva.utils import color


def define_bg(r, g, b):
    return f"\033]11;{color.to_hex(r, g, b)}\007"


def switch_bg(r, g, b):
    r, g, b = (round(c * 255) for c in (r, g, b))
    return f"\033[48;2;{r};{g};{b}m\007"


hide_cursor = "\033[?25l"
show_cursor = "\033[?25h"
reset_colors = "\033(B\033[m"
clear_screen = "\033[H\033[2J"
