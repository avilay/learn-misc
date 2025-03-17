import hydra

# $ python main.py cmd=train eval_checkpoint=.
@hydra.main(config_path=".", config_name="config", version_base=None)
def main(cfg):
    print("App name: ", cfg.app.name)
    print("Invoked cmd: ", cfg.cmd)
    print("Eval checkpoint: ", cfg.eval_checkpoint)


if __name__ == "__main__":
    main()
