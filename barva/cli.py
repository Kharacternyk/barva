from argparse import ArgumentParser
from inspect import getfullargspec


def to_cli_flag(arg):
    return "--" + arg.rstrip("_")


def extract_description(frontend):
    return frontend.__doc__.splitlines()[0]


def cli(cmds):
    parser = ArgumentParser()
    subparsers = parser.add_subparsers(
        required=True,
        metavar="frontend",
        dest="frontend",
    )
    for name, frontend in cmds.items():
        desc = extract_description(frontend)
        subparser = subparsers.add_parser(name, help=desc, description=desc)
        spec = getfullargspec(frontend)
        for arg in spec.kwonlyargs:
            subparser.add_argument(
                to_cli_flag(arg),
                default=spec.kwonlydefaults[arg],
                type=spec.annotations[arg],
            )
    args = parser.parse_args()
    frontend = cmds[args.frontend]
    del args.frontend
    for val in frontend(**vars(args))():
        if val is not None:
            print(val)
