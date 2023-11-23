# TransitPilot

Console-based public transport route finder program

## Examples

These examples are using the [demo-config.txt](configs/demo-config.txt) configuration file.

The map for the demo ([file](configs/maps/demo-config.svg)):

![file](configs/maps/demo-config.svg)

### Basic route

Plan a route when the two stops are on the same line.

#### Steps:

1. List all the stops for the ids (optional)
2. Set `Stop A` to `Prince Lane`
3. Set `Stop B` to `Walnut route`
4. Start the route planning

### Advanced route

Plan a route, but the two stops are not on the same line.

#### Steps:

1. List all the stops for the ids (optional)
2. Set `Stop A` to `Sycamore Route`
3. Set `Stop B` to `Vermilion Lane`
4. Start the route planning

## Start the program

To start the find compile the source code then find the created executable (`path\to\TransitPilot.exe`). Start the program with the following command template:

```bash
".\path\to\TransitPilot.exe" ".\path\to\config_file.txt"
```

Change the `.\path\to` section of the command to your file's path.

## Custom configuration file

To create a custom configuration file, use the config file template below:

```
sign;first stop;time between first and second stop;second stop[;time between second and third stop;third stop]
```

Example for custom configuration file: [demo-config.txt](.\configurations\demo-config.txt)

## Copyright notice

> Copyright &copy; 2023 [László Mócsy](https://www.laszlomocsy.hu)
