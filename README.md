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
PS C:\Users\Jared Gajulin\Desktop\fileusage\x64\Release> .\fileusage-benchmark.exe c:\

fileusage_benchmark {v1.0.0} (c) 2024, Jared Gajulin
Root directory is: "c:\\"

fileusage.exe:
        Execution time info:
                Nanoseconds: 43,691,260,900ns
                Microseconds: 43,691,260us
                Milliseconds: 43,691ms
                Seconds: 43.6913s

        Execution time info (cout disabled):
                Nanoseconds: 4,520,855,500ns
                Microseconds: 4,520,855us
                Milliseconds: 4,520ms
                Seconds: 4.52086s

fileusage-demo.exe:
        Execution time info:
                Nanoseconds: 56,522,698,500ns
                Microseconds: 56,522,698us
                Milliseconds: 56,522ms
                Seconds: 56.5227s

        Execution time info (cout disabled):
                Nanoseconds: 22,174,823,400ns
                Microseconds: 22,174,823us
                Milliseconds: 22,174ms
                Seconds: 22.1748s
```