#!/usr/bin/env python
from fire import Fire
from frontends import *


def main():
    try:
        Fire()
    except KeyboardInterrupt:
        print()


if __name__ == "__main__":
    main()
