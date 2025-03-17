import click


@click.group()
def main():
    """
    A group means that this CLI can be invoked as -
    `python cmds.py hello ...`
    - or -
    `python cmds.py namaste ...`

    This particular main function does not have to do anything. It can do some
    initializaiton if needed.

    There two main "commands" - hello and namaste. Both correspond to the function names.
    Each command can set its own options and arguments.
    """
    pass


@main.command()
@click.option("--count", default=1, help="The number of greetings.")
@click.argument("name")
def hello(count, name):
    """
    This command has set one option and one argument.
    """
    for _ in range(count):
        print("Hello ", end="")
    print(name)


@main.command()
def namaste():
    """
    This command has set no arguments or options.
    """
    print("Namaste duniya")


if __name__ == "__main__":
    main()
