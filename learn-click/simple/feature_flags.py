import sys
import click


@click.command()
@click.option("--upper", "transformation", flag_value="upper", default=True)
@click.option("--lower", "transformation", flag_value="lower")
def info(transformation):
    click.echo(getattr(sys.platform, transformation)())


if __name__ == "__main__":
    info()
