import click

"""
$ python args.py --help
Usage: args.py [OPTIONS] NAME

  This program has one option and one positional argument.

Options:
  --count INTEGER  The number of greetings.
  --help           Show this message and exit.

$ python args.py aptg
Hello aptg

$ python args.py --count 2 aptg
Hello Hello aptg

$ python args.py --count=2 aptg
Hello Hello aptg
"""


@click.command()
@click.option("--count", default=1, help="The number of greetings.")
@click.option("--slow/--fast", default=True, help="Fast or slow?")
@click.argument("name")
def main(count, name, slow):
    "This program has one option and one positional argument. This is where I explain what the requirement argument means."
    print("count: ", count)
    print("name: ", name)
    print("slow: ", slow)


if __name__ == "__main__":
    main()
