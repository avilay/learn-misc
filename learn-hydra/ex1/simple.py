"""
To run with the existing config in simple.yaml -
    python simple.py

To override the config value db.user -
    python simple.py user=lala

To add a new value in the config -
    python simple.py schema=books

To simply print the effective config and exit use the `--cfg job` option:
    python simple.py user=lala --cfg job
"""

import hydra
from omegaconf import DictConfig


@hydra.main(config_path=".", config_name="simple")
def main(cfg: DictConfig):
    print(cfg.driver)
    print(cfg.user)
    print(cfg["password"])
    print(cfg)
    for key, value in cfg.items():
        print(key, value)


if __name__ == "__main__":
    main()
