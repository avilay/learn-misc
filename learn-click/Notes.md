# CLI Arguments
There are three basic types of CLI arguments
  * Arguments
  * Options
  * Commands

## Arguments
These are simple positional arguments passed to the executable without any decorations.

```shell
touch foo.txt
```

### Variadic Arguments
When we want th pass any number of arguments to the executable.

```shell
copy foo.txt bar.txt myfolder
```

### File Path Argument
Click has some convenience functionality if we specifcy that the argument is supposed to be a file path.

## Options
These are switches, preceeded by a `-` or a `--`.

### Basic Value Options
Are a pair of switch name and its value. Can be in any order.

```shell
dots --num=2 --style=*
dots --style=* --num=2
```
These can be required or optional (default), have a default value or not.

### Multivalue Options
The same switch can be followed by multiple values, all of which should be gathered up as the value for that switch.

```shell
findme --pos 2 5 9
```

### Multiple Options
The same switch can be provided multiple times with different values.

```shell
commit -m foo -m bar
```

### Counting
The same opiton can be repeated multiple times and the reptition count is the value for that option.

```shell
log -vvv
```

### Boolean Flags
These come in different varities. They can either have a true option and a false option -

```shell
info --shout
info --no-shout
```

Or they can only have true option, false is assumed by the absence of true.

```shell
info --shout
info [This is taken as not shout]
```

### Feature Switches
Lets say I have a feature called `dial` that can be set to three values `high`, `medium`, and `low`. The external interface will not know about `dial`, it will only know about the values. Internally whatever value is provided is gathered into the `dial` feature.

```shell
deploy --high
deploy --medium
deploy --low
```

### Choice Options
When I want to restrice the values that can be provided to the switch, I can specify them as choices. Lets say I have an option `--processor` and it can only take `gpu`, `tpu`, and `cpu` as values. Any other value should result in an error.

```shell
train --processor gpu
train --processor cpu
trian --processor tpu
train --processor mtia [error!]
```

### Prompts
These options can either by supplied on the CLI, or the program can ask the user for this option if it is absent.

#### Password Prompts
Similar to the above, but the value will not be shown as it is typed.

## Commands
These are `git`-like commands where they can do multiple things like `git add`, `git commit`, `git amend`, etc. each with its own arguments and options.
