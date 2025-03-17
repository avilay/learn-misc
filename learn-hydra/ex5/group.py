"""
See conf/config.yaml.

To run with the default config:
    python group.py --cfg=job

To override specific values:
    python group.py db.user=lala --cfg=job
    python group.py schema.tables.1.name=tests --cfg=job

To override an entire section:
    python group.py db=postgres

To override a section and a value within it:
    python group.py db=postgres db.timeout=20

To override a section and a value in another section:
    python group.py db=postgres schema.tables.1.name=tests
"""

import hydra


@hydra.main(config_path="conf", config_name="config")
def main(cfg):
    pass


if __name__ == "__main__":
    main()
