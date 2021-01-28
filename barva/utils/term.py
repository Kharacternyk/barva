from os import access
from os import scandir
from os import W_OK


def change_bg(color):
    return f"\033]11;{color}\007"


def to_all(msg):
    for entry in scandir("/dev/pts"):
        if access(entry.path, W_OK):
            with open(entry.path, "w") as file:
                print(msg, file=file, end="", flush=True)
