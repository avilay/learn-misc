import hydra
from omegaconf import DictConfig
import platform


@hydra.main(config_path=".", config_name="sections")
def main(cfg: DictConfig):
    if platform.system() == "Darwin":
        create_db = cfg.ui.osx.create_db
        view = cfg.ui.osx.view
        print(
            f"I am on mac and will create the db: {create_db} and will set up the view: {view}"
        )
    else:
        print("What?!?!")


if __name__ == "__main__":
    main()
