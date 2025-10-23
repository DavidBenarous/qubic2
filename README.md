A novel biclustering algorithm for analyses of transcriptomic data. 
For basic introduction regarding installation and running QUBIC2, please refer to http://bmbl.sdstate.edu/github/qubic2/qubic2_tutorial.html.
For details regarding the parameters, please refer to the README file. 

## Wolfram Mathematica Integration

This project can be compiled as a shared library and used within Wolfram Mathematica to perform biclustering analysis.

### Compilation

To build the shared library, use the `shared` target in the makefile.

*   **On Linux/macOS:**
    ```bash
    make shared
    ```
    This will produce a `qubic.so` file.

*   **On Windows:**
    You will need to have the Visual Studio compiler toolchain set up. Open a developer command prompt and run:
    ```bash
    nmake /f makefile shared
    ```
    This will produce a `qubic.dll` file.

### Usage in Mathematica

You can load the compiled library into your Mathematica session using the `LibraryFunctionLoad` command.

**Example:**

```mathematica
(* Load the library function *)
(* Replace "/path/to/your/compiled/library/" with the actual path to the compiled library file *)
qubicRun = LibraryFunctionLoad["/path/to/your/compiled/library/qubic.so", "run_qubic", {"UTF8String", "UTF8String"}, "UTF8String"];

(* Define the input file path and clustering options *)
inputFile = "/path/to/your/data/example";
options = "-k 10 -c 0.9 -o 5"; (* Example options: min column width 10, consistency 0.9, report 5 blocks *)

(* Call the function *)
results = qubicRun[inputFile, options];

(* Print the results *)
Print[results];
```

#### Function Signature

The `run_qubic` function has the following signature:

`run_qubic(input_file, options_str)`

*   **`input_file` (String):** The full path to the input data file. The file should be in the format described in the [QUBIC tutorial](http://bmbl.sdstate.edu/github/qubic2/qubic2_tutorial.html).
*   **`options_str` (String):** A string containing the command-line options for the biclustering algorithm. These are the same options you would use when running the command-line version of QUBIC.

#### Output

The function returns a single string containing the biclustering results, which includes the identified biclusters and their associated genes and conditions.
