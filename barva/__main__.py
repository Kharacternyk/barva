#!/usr/bin/env python
import frontends
from fire import Fire


def main():
    try:
        Fire(frontends)
    except KeyboardInterrupt:
        print()


if __name__ == "__main__":
    main()
