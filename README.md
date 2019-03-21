# QM // Quick modeling tool

## Building
### Prerequisites
#### Dependencies
- [libyaml-cpp](https://github.com/jbeder/yaml-cpp)
- [ns-3-dce (dce-linux-1.10)](https://ns-3-dce.readthedocs.io/en/latest/getting-started.html#build-dce)

For distributed modeling NS-3 and DCE should be builded with --with-mpi / --enable-mpi options.

#### Toolchain
- cmake@3.13 or higher
- clang@7.0 or higher

#### Required environment variables
|  Name      | Description                    | Example value                                    |
|------------|--------------------------------|--------------------------------------------------|
| `DCE_HOME` | Absolute path to DCE directory | `home/csepanda/Work/DCE`                         |
| `DCE_ROOT` | Absolute path to built DCE     | `$DCE_HOME/build`                                |
| `DCE_PATH` | PATH to built DCE's executable | `$DCE_ROOT/bin:$DCE_ROOT/bin_dce:$DCE_ROOT/sbin` |
### Build
```
cmake .
make
```

## Running
### Prerequisites
#### Required environment variables
|  Name             | Description                    | Example value                                    |
|-------------------|--------------------------------|--------------------------------------------------|
| `DCE_PATH`        | PATH to built DCE's executable | `$DCE_ROOT/bin:$DCE_ROOT/bin_dce:$DCE_ROOT/sbin` |
| `LD_LIBRARY_PATH` | PATH to built DCE's libraries  | `$DCE_ROOT/lib:$LD_LIBRARY_PATH`                 |

### Run
```
./qm-runner <YAML_CONFIG>
```

### Other tools
#### ./tools/examine-files.bash
Show all last runned model's processes in nodes and exit status

### ./tools/clean-simulation-files.bash
Remove all files created during the simulation
