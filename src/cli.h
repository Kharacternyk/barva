struct cli_options {
    int queue_depth;
};

struct cli_options parse_cli_options(int argc, char *argv[]);
