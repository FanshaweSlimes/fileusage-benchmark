# fileusage-benchmark

### ⚠️ Warning ⚠️
Cold caching can theoretically have any of the programs access cache instead of actual read I/O, displaying inaccurate results. [See system file cache.](https://learn.microsoft.com/en-us/windows/win32/fileio/file-caching) For more fair results, this program will only benchmark the warm cache.

### Purpose
This project provides a benchmark utility to directly compare the performance of the "fileusage" binary against a provided binary named "fileusage-demo". 
* This was specifically made for Project #3 (2nd term) of the CPA3 program.

### Prerequisites
* **Binaries:** One or the other "fileusage.exe" and "fileusage-demo.exe" files must be present in the project's directory. (This is useful if you only want to benchmark one binary.)
* **Operating System:** Designed for Windows environments.

### Usage
1. **Compile:**  If not already compiled, build the project to generate the "fileusage-benchmark" executable.
2. **Run:** Execute the following command from the command line within the project directory:
    ```bash
    fileusage-benchmark [optional_root_directory]
    ```
   * Replace `[optional_root_directory]` with the desired root directory for the "fileusage" and "fileusage-demo" binaries to operate on. If omitted, the current directory is used.

### Output
The benchmark utility provides a clear textual output with the following:
* Identification of the version and author
* The root directory used for the file operations
* Detailed execution times for each binary (nanoseconds, microseconds, milliseconds, seconds)
* Notes indicating if standard console output (cout) was suppressed during a benchmark run

### Notes
* The benchmark redirects console output to `NUL` to focus purely on execution time.
* For more comprehensive benchmarking, run multiple iterations of the tool.

### Example Output
```bash
fileusage-benchmark {v1.1.0} (c) 2024, Jared Gajulin
Root directory is: "c:\\"

fileusage-demo.exe:
        Execution time info:
                Nanoseconds: 34,725,013,100ns
                Microseconds: 34,725,013us
                Milliseconds: 34,725ms
                Seconds: 34.725s

        Execution time info (cout disabled):
                Nanoseconds: 20,511,902,600ns
                Microseconds: 20,511,902us
                Milliseconds: 20,511ms
                Seconds: 20.5119s

fileusage.exe:
        Execution time info:
                Nanoseconds: 15,225,695,400ns
                Microseconds: 15,225,695us
                Milliseconds: 15,225ms
                Seconds: 15.2257s

        Execution time info (cout disabled):
                Nanoseconds: 3,924,636,400ns
                Microseconds: 3,924,636us
                Milliseconds: 3,924ms
                Seconds: 3.92464s
```