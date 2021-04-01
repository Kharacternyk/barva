from argparse import ArgumentDefaultsHelpFormatter
from argparse import ArgumentParser
from argparse import MetavarTypeHelpFormatter
from inspect import getfullargspec

from barva.sources import NativeSource


class Formatter(ArgumentDefaultsHelpFormatter, MetavarTypeHelpFormatter):
    pass


def to_cli_flag(arg):
    return "--" + arg.rstrip("_")


def extract_frontend_description(frontend):
    return frontend.__doc__.splitlines()[0]


def extract_arg_description(frontend, arg):
    lines = frontend.__init__.__doc__.splitlines()
    while not lines[0].lstrip().startswith(arg + ":"):
        lines = lines[1:]
    return lines[0].lstrip().replace(arg + ":", "")


def cli(cmds):
    parser = ArgumentParser()
    subparsers = parser.add_subparsers(
        required=True,
        metavar="frontend",
        dest="frontend",
    )
    for name, frontend in cmds.items():
        desc = extract_frontend_description(frontend)
        subparser = subparsers.add_parser(
            name, help=desc, description=desc, formatter_class=Formatter
        )
        spec = getfullargspec(frontend)
        for arg in spec.kwonlyargs:
            subparser.add_argument(
                to_cli_flag(arg),
                help=extract_arg_description(frontend, arg),
                default=spec.kwonlydefaults[arg],
                type=spec.annotations[arg],
            )
    args = parser.parse_args()
    frontend_type = cmds[args.frontend]
    del args.frontend
    with frontend_type(**vars(args)) as frontend, NativeSource(
        frontend.sampling_requirements
    ) as backend:
        try:
            for samples in backend:
                value = frontend(samples)
                if value is not None:
                    print(value)
        except KeyboardInterrupt:
            pass
