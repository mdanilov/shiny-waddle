# shiny-waddle

Implements `In Memory File Cache Design` specified in `task.md`.

## Development environment
- Ubuntu 20.04
- CMake 3.15.3
- gcc 9.3.0
- GTest library (release-1.8.0) is fetched by the CMake
- (Optional) Ruby to run the integration tests

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
./run_basic_example.sh
```

There is `rakefile` (Ruby script) which allows to run the test on random data
```
rake test:random # run tests on randomly generated data
rake test:big # run test on `big` example data
rake test:gen # generate random test
```

## Generate documentation
The documentation can be generated using the `Doxygen` command. The output will be in the `doc` folder.
```
doxygen
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

### Results
Tests results on randomly generated data with 10 readers, 2 writers and 1000 items.
Data access is fully random. Each Reader is doing 10000 reads, and each writer 1000 writes.

Output from the `rake test:random` command.
It runs the tests with different cache sizes (1, 10, 50, 100, 200, 500).

**Note: It hard to achieve the clear tests result in terms of the execution time, because of OS cache for file operations and CPU cache**

```
== Test #1, cache = 1 ==
Reader1.txt.out: 9990 Disk, 10 Cache
Reader10.txt.out: 9907 Disk, 93 Cache
Reader2.txt.out: 9969 Disk, 31 Cache
Reader3.txt.out: 9973 Disk, 27 Cache
Reader4.txt.out: 9958 Disk, 42 Cache
Reader5.txt.out: 9956 Disk, 44 Cache
Reader6.txt.out: 9943 Disk, 57 Cache
Reader7.txt.out: 9924 Disk, 76 Cache
Reader8.txt.out: 9937 Disk, 63 Cache
Reader9.txt.out: 9902 Disk, 98 Cache
Execution time: 8.20505448 seconds
== Test #2, cache = 10 ==
Reader1.txt.out: 9899 Disk, 101 Cache
Reader10.txt.out: 9005 Disk, 995 Cache
Reader2.txt.out: 9813 Disk, 187 Cache
Reader3.txt.out: 9696 Disk, 304 Cache
Reader4.txt.out: 9580 Disk, 420 Cache
Reader5.txt.out: 9478 Disk, 522 Cache
Reader6.txt.out: 9397 Disk, 603 Cache
Reader7.txt.out: 9291 Disk, 709 Cache
Reader8.txt.out: 9185 Disk, 815 Cache
Reader9.txt.out: 9125 Disk, 875 Cache
Execution time: 7.747502976 seconds
== Test #3, cache = 50 ==
Reader1.txt.out: 9490 Disk, 510 Cache
Reader10.txt.out: 5020 Disk, 4980 Cache
Reader2.txt.out: 9004 Disk, 996 Cache
Reader3.txt.out: 8499 Disk, 1501 Cache
Reader4.txt.out: 8018 Disk, 1982 Cache
Reader5.txt.out: 7456 Disk, 2544 Cache
Reader6.txt.out: 6991 Disk, 3009 Cache
Reader7.txt.out: 6529 Disk, 3471 Cache
Reader8.txt.out: 5960 Disk, 4040 Cache
Reader9.txt.out: 5529 Disk, 4471 Cache
Execution time: 9.002276492 seconds
== Test #4, cache = 100 ==
Reader1.txt.out: 8991 Disk, 1009 Cache
Reader10.txt.out: 196 Disk, 9804 Cache
Reader2.txt.out: 7990 Disk, 2010 Cache
Reader3.txt.out: 7002 Disk, 2998 Cache
Reader4.txt.out: 5961 Disk, 4039 Cache
Reader5.txt.out: 4948 Disk, 5052 Cache
Reader6.txt.out: 4023 Disk, 5977 Cache
Reader7.txt.out: 2977 Disk, 7023 Cache
Reader8.txt.out: 2013 Disk, 7987 Cache
Reader9.txt.out: 1080 Disk, 8920 Cache
Execution time: 9.379837932 seconds
== Test #5, cache = 200 ==
Reader1.txt.out: 7991 Disk, 2009 Cache
Reader10.txt.out: 27 Disk, 9973 Cache
Reader2.txt.out: 5989 Disk, 4011 Cache
Reader3.txt.out: 3975 Disk, 6025 Cache
Reader4.txt.out: 2030 Disk, 7970 Cache
Reader5.txt.out: 105 Disk, 9895 Cache
Reader6.txt.out: 30 Disk, 9970 Cache
Reader7.txt.out: 34 Disk, 9966 Cache
Reader8.txt.out: 46 Disk, 9954 Cache
Reader9.txt.out: 31 Disk, 9969 Cache
Execution time: 8.495589749 seconds
== Test #6, cache = 500 ==
Reader1.txt.out: 4975 Disk, 5025 Cache
Reader10.txt.out: 19 Disk, 9981 Cache
Reader2.txt.out: 293 Disk, 9707 Cache
Reader3.txt.out: 81 Disk, 9919 Cache
Reader4.txt.out: 52 Disk, 9948 Cache
Reader5.txt.out: 32 Disk, 9968 Cache
Reader6.txt.out: 31 Disk, 9969 Cache
Reader7.txt.out: 42 Disk, 9958 Cache
Reader8.txt.out: 21 Disk, 9979 Cache
Reader9.txt.out: 18 Disk, 9982 Cache
Execution time: 7.639138672 seconds
```