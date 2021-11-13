# shiny-waddle

Implements `In Memory File Cache Design` specified in `task.md`.

## Development environment
- Ubuntu 20.04
- CMake 3.15.3
- gcc 9.3.0
- GTest library (release-1.8.0) is fetched by the CMake

C++11 and Linux are the main constraints.

# Getting Started

Project structure:
- **examples** contains test configuration files for unit and integration tests
- **include** application headers
- **mock** contains interfaces mocks (GMock). Used by unit tests.
- **src** application sources
- **test** unit tests

All commands needs to be run from the root workspace folder.

## Build
Builds the `executor` executable file. The result can be found under `build` folder.
```
./build.sh
```

## Run tests
Tests are written using the GTest and to the CMake configuration, those can be run with `ctest`.
The command below runs build first, and remove all tests output temporary files.
```
./run_tests.sh
```

## Run example
This command runs `executor` binary with command line arguments of the example from the `task.md`.
It also builds first and clean-up the workspace from the files of previous runs.
`Items.txt` file is restored to it's initial state.
```
./run_example.sh
```

## Requirements analysis
- Statement `Design and implement an efficient eviction mechanism when there is a cache miss.` is unclear.
  The efficient eviction mechanism is depend on the applied use case, which is not specified. So it's not possible
  to implement efficient, but considering `performs caching of frequently accessed items` assume that LFU cache mechanism should be
  implemented. The final solution will contain both LFU and LRU cache implementations, while LFU cache is default.

- `Handle the case of dirty cache item, where a writer is modifying the item that is already cached.` It does not specify whether
  the writer can change the cache rather than only modifying already existing items, so assume that writer can't remove/add items
  to the cache. And in case of LFU cache, writer does not increase the frequency access counter.

- `Your program should handle all corner cases and robust to failures. If it fails, it should fail gracefully giving out meaningful failure messages.`
  In case of unrecoverable error the program returns code 1 and prints the error message to `stdout`. In general all error messages are goes to `stdout`.

## Overview

The program spawns N (number of the readers) + M (number of writers) threads according the configuration from the .txt files. This configuration files are passed through the command line arguments. Each reader has it's own `ReaderX.txt` configuration file, the same for writer - `WriterX.txt`.
Readers and writes access shared text file `Items.txt`, each line of file contains text value and indexed from 1. Access to that file is cached.
The size of cache is specified from the command line parameter, and the type is least frequently used (LFU). So cache contains most frequently accessed items and accessed here means **read**. Each reader writes read value to the `ReaderX.txt.out` in the format `<read_value> <Disk or Cache>`.

### Architecture
Since we have multiple readers and writers that needs to access the same object from different threads, the access should be synchronized.
There are 2 mutexes, one for the cache memory and another for the file access. Thereby it's possible to have readers are reading from
the cache, while the writer is writing to the file at the same time. Both mutexes has `shared` type and used in the way that multiple
reader can access the objects at the same time (shared lock), while there can be only one writer (unique lock).

As mentioned above the cache is implemented using the LFU algorithm. For each `read` access a counter associated with the index is incremented,
so there is history how many times each index is accessed. And when this counter is greater than the counter of the LFU element in the cache the new element is added to the cache, while the LFU is removed.
