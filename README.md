# shiny-waddle

# Build
Run the following command from the workspace root folder:
```
mkdir build && cmake .. && make
```

The built executable `executor` can be found under `build` folder.

# Run
```
cd examples/basic && ../../build/executor 4 Reader.txt Writer.txt Items.txt
```