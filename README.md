# CACHE Simulator

### How to use

1. **Inside the project folder**, execute **generate_initial_data.cpp** 
to get a file called *"initial_data"* inside `/initial_data`:
```
$ g++ -std=c++14 -o ./initial_data/generate_initial_data ./initial_data/generate_initial_data.cpp
$ ./initial_data/generate_initial_data > initial_data/initial_data
```
2. After that, execute  **generate_trace.cpp** to get a file called *"trace"* inside `/trace`:
```
$ g++ -std=c++14 -o ./trace/generate_trace ./trace/generate_trace.cpp
$ ./trace/generate_trace > trace/trace
```
3. Then execute **cache_simulator.cpp** with the generated *trace input* and get the results:
```
$ g++ -std=c++14 -o cache_simulator cache_simulator.cpp
$ ./cache_simulator < trace/trace
```

> ### Suggestions
> * Change **generate_trace.cpp** to get diferent results.
