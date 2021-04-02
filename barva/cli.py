from argparse import ArgumentDefaultsHelpFormatter
from argparse import ArgumentParser
from argparse import MetavarTypeHelpFormatter
from inspect import getfullargspec

from barva.sources import NativeSource


class Formatter(ArgumentDefaultsHelpFormatter, MetavarTypeHelpFormatter):
    pass


def extract_visualizer_description(visualizer):
    return visualizer.__doc__.splitlines()[0]


def extract_arg_description(visualizer, arg):
    lines = visualizer.__init__.__doc__.splitlines()
    while not lines[0].lstrip().startswith(arg + ":"):
        lines = lines[1:]
    return lines[0].lstrip().replace(arg + ":", "")


def cli(cmds):
    parser = ArgumentParser()
    subparsers = parser.add_subparsers(
        required=True,
        metavar="visualizer",
        dest="visualizer",
    )
    for name, visualizer in cmds.items():
        desc = extract_visualizer_description(visualizer)
        subparser = subparsers.add_parser(
            name, help=desc, description=desc, formatter_class=Formatter
        )
        spec = getfullargspec(visualizer)
        for arg in spec.kwonlyargs:
            subparser.add_argument(
                "--" + arg,
                help=extract_arg_description(visualizer, arg),
                default=spec.kwonlydefaults[arg],
                type=spec.annotations[arg],
            )
    args = parser.parse_args()
    visualizer_type = cmds[args.visualizer]
    del args.visualizer
    with visualizer_type(**vars(args)) as visualizer, NativeSource(
        visualizer.sampling_requirements
    ) as source:
        try:
            for samples in source:
                value = visualizer(samples)
                if value is not None:
                    print(value)
        except KeyboardInterrupt:
            pass
