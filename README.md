# TransitPilot

Console-based public transport route finder program

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

```
ABC123;FirstStop;1;SecondStop;2;ThirdStop;3;FourthStop;4;FifthStop;5;SixthStop
```

Example for custom configuration file: [demo-config.txt](.\configurations\demo-config.txt)

## Copyright notice

> Copyright &copy; 2023 [László Mócsy](https://www.laszlomocsy.hu)
