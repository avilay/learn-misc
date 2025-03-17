import click


@click.command()
def main():
    """
    This is just like any other main function. But the decorator automatically adds a --help
    option and prints the usage along with this docstring.
    """
    print("Hello click!")


if __name__ == "__main__":
    main()
