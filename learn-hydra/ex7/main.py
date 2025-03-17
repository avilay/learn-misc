import logging
import hydra
from .pkg import func

# A logger for this file
log = logging.getLogger(__name__)


@hydra.main(config_path=".", config_name="config")
def my_app(cfg):
    log.info("Info level message")
    log.debug("Debug level message")
    func()


if __name__ == "__main__":
    my_app()
