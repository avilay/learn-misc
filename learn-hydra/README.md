# Hydra

## Basics

Decorating the `main` method with `@hydra.main` and providing the config filepath tells Hydra where to find the base config file. At its simplest the config file is a map of key/values:

```yaml
driver: mysql
user: aptg
password: secret
```

It is possible to override the config path and config name at the command line as follows:
```
python simple.py --config-path=/Users/avilay/temp --config-name=simple_2.yaml
```

The config contents are available to the decorated `main` function as a `DictConfig` object, which means that the items can be referenced using the `.` operator instead of having to use the usual Python `dict` accessors. On the CLI, user can override specific values in the config like so -

`python simple.py user=lala`

We can even add new values to the config on the CLI without touching the config file by using `+` like so -

`python simple.py +schema=books`

Notice that in the original config file there is no entry for `schema`. 

> Hydra provides a helpful debugging CLI option `cfg=job` that will just dump the **effective** config on stdout and exit.

See `ex1` for a simple example.

A typical config yaml file has multiple sections as seen in `sections.yaml`. Think of these as nested maps.

```yaml
db:
  driver: mysql
  user: aptg
  password: secret

ui:
  windows:
    create_db: true
    view: true
  osx:
    create_db: false
    view: true
```

And these can referenced in the code as `cfg.ui.windows.create_db`. On the CLI they can overridden in a similar fashion -

`python sections.py ui.osx.view=false`

See `ex2` for an example with sections.

The config values can be interpolated with keys like so -

```yaml
db:
	driver: mysql
	user: aptg
	password: secret
	host: ${db.driver}://localhost
```

## Defaults

Building on the `sections.yaml`, another typical scenario is to have both `windows` and `osx` configs in their own seperate files with the main config specifying a default config which the user can override as always.

```yaml
defaults:
  - ui: osx

db:
  driver: mysql
  user: aptg
  password: secret
```

Here Hydra will figure out that there should be another key called `ui` at the root level. But the value of this key is specified in a file called `./ui/osx.yaml`. The path of the file should mirror the key path. In `osx.yaml` we don't need to specify the `ui` key again, we just specify the value of this key, which is just another map.

```yaml
create_db: false
view: true
```

On the CLI I can then specify the windows platform as follows:

`python main.py ui=windows`.

As with the defaults section, Hydra will look for a file `./ui/windows.yaml` to plug in the value of the `ui` key.

See `ex3` for this example.

The logic of the file path to look for in the defaults section is not very smart. E.g., if I have:

```yaml
defaults:
	- schama.schools: northshore
```

Hydra is **not** going to look for `./schema/schools/northshore.yaml`. It is going to look for `./schema.schools/northshore.yaml`. So everything in the key name must be the actual name of the directory. And defaults section cannot contain a dict itself, so there is no way to specify the following:

```yaml
defaults:
	- schema:
			schools: northshore
```

This will throw an error. The way to have nested directories is to specify the main key like this:

```yaml
defaults:
	- schema/schools: northshore
```

This will now look for `./schema/schools/northshore.yaml`. See `ex4` for a worked out example. See `ex5` for a more extensive example using sub-configs.

## Help

Hydra comes with default help documentation that pretty much prints out the entire effective config upon getting the `--help` flag. We can customize the help string by adding the following node to the main config file:

```yaml
hydra:
	help:
		template: |-
			help contents here
```

`hydra.help` has a bunch of well known keys like `app_name`, `header`, etc. that we can use inside the `template` section using the `${hydra.help.app_name}` type syntax. I can also tuck the help documentation into a separate yaml file and set it using the `defaults` section like so:

```yaml
defaults:
	- override hydra/help: doc
```

This means that Hydra will look for `./hydra/help/doc.yaml` and substitute its contents as the value of `hydra.help` node.

## Logging

Hydra configures Python's logging module to log `INFO` level logs to both the console as well as the log file in the default working directory. To change the working directory add the following config in the main config (or tuck it away in a separate config as shown in the **Help** section above):

```yaml
app:
  name: ddp-binclass-app

hydra:
  run:
    dir: /Users/avilay/mlruns/${app.name}/${now:%Y-%m-%d_%H-%M}
```

See `ex7` for a working example. I can also change the formatter. Just see the `hydra.logging` in the generated `hydra.yaml` file in any of the output directories and change whatever I want to in my main app config.







