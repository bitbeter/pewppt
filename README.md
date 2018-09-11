# Performance engineering with performance profiling tools (PEWPPT)
This project show exmaples of performance optimization with help of `perf` witch is a performance profiling tool.  
You can see the presentation pdf and run demos in your linux.

## Perf
Perf is an amazing performance mesaurement tool that use unknown profiling tool built into the linux kernal. It is easy to install and run and can be used either for quick analysis of what the whole system is doing (perf top) or advanced analysis and comparisions of multiple program benchmarking runs (perf record).

### Installing
You need install kernel specific Perf binary package.

```shell
sudo apt-get update
sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`
```

> uname -r  
> Used for cheking your linux kernel version.
> This is important that you install linux-tools with compatibility of your linux kernel.

You should now have the `perf` command. Run it as root like:

    sudo perf --help

### Perf top

Running `perf top` will provide a real-time aggregate of functions where most of the time is spent across all cpu's and processes.

    sudo perf top


### Perf record

To isolate profiling to a single process or program use `perf record`. You can launch a process under `perf record` or attach to an already running process

Run a program with `perf record` and profile until the program exits:

    sudo perf record ./test-program

Attach to a running program:

    sudo perf record --pid `pidof program-name` # ctrl-c to stop recording

Handy options to perf record are:
 - `-a`: force `perf record` to track all cpus
 - `-g`: generates call graph information

NOTE: more recent `perf` versions may require an argument tobe passed after the `-g` like `dwarf`

### Perf report

To view the profiling results you use `perf report`.

To bring up an interactive console interface with details do:

    sudo perf report

To dump out all the details of the report to a shareable text file do:

    sudo perf report > profiling-results.txt

### Perf additional docs

- The developers notes: <http://lxr.free-electrons.com/source/tools/perf/Documentation/examples.txt>
- Compared to oprofile/gprof: <http://rhaas.blogspot.com/2012/06/perf-good-bad-ugly.html>
- Detailed wiki with tutorial: <https://perf.wiki.kernel.org/index.php/Main_Page>


## Requierments

### install `pmu-tools`
```shell
git clone git://github.com/andikleen/pmu-tools 
```

### install `autofdo`
```shell
apt-get install autofdo
```

## Presentation Demos

### C1
With Clock

```shell
##### PART1 #####
# Compile sort.c
gcc sort.c -o sort.o
# Run
./sort.o
# Run with input
./sort.o 100000

##### PART2 #####
# Run with Perf
sudo perf stat ./sort.o
# Compile sort.c with debug flag
gcc sort.c -o sort.o
```

### C2
https://gcc.gnu.org/wiki/AutoFDO/Tutorial
```shell
##### PART1 #####
# Compile with optimization flags
gcc -O3 sort.c -o sort_optimized.o
# Run
sudo perf stat ./sort_optimized.o

##### PART2 #####
# Compile with gcc built-in profiler
gcc sort.c -o sort_instrumented.o -fprofile-generate
# Run
sudo perf stat ./sort_instrumented.o
# Give gcda file to compiler
gcc -O3 sort.c -o sort_fdo.o -fprofile-use=sort.gcda
# Run
sudo perf stat ./sort_fdo.o

##### PART3 #####
# AutoFDO
gcc sort.c -o sort.o
# Profiling
ocperf.py record -b -e br_inst_retired.near_taken:pp -- ./sort.o
# Generate GCC standard profiled file
create_gcov --binary=./sort.o --profile=perf.data --gcov=sort.gcov -gcov_version=1
# Use Profile file
gcc -O3 -fauto-profile=sort.gcov sort.c -o sort_autofdo.o
# Run 
sudo perf stat ./sort_autofdo.o
```

### C3
```shell
##### PART1 #####
# Compile with optimization flags
gcc sort.c -o sort.o
# OR
gcc sort.c -o sort.o -DARRAY_LEN=10000000
# Run
sudo perf stat ./sort.o

##### PART2 #####
gcc sort_branchless.c -o sort_branchless.o -g
# Run
sudo perf stat ./sort_branchless.o
# Record program
sudo perf record
# Show Annotate
perf annotate
```

## C4
```shell
# NOT COMPLETED
```


## C5
```shell
# example1 compile
gcc example.c -o example.o
# Run example1
./example.o
# Run perf top
sudo perf top --pid `pidof example.o`
# Run perf record
sudo perf record --pid `pidof example.o`
# OR
sudo perf record sleep 10 ./example.o
# Repeat profiling
sudo perf stat -r 2 sleep 5 ./example.o
```