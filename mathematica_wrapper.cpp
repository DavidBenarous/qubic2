#include "main.h"
#include "get_options.h"
#include "read_array.h"
#include "make_graph.h"
#include <sstream>
#include <vector>
#include <string>

/*
 * HOW TO USE WITH WOLFRAM MATHEMATICA:
 *
 * 1. Compile the shared library.
 *    - On Linux/macOS, run `make shared` to create `qubic.so`.
 *    - On Windows, you will need to have the Visual Studio compiler toolchain set up.
 *      Run `nmake /f makefile shared` in a developer command prompt to create `qubic.dll`.
 *
 * 2. Load the library in Mathematica.
 *    - Make sure the compiled library file is in a location where Mathematica can find it.
 *    - Use the `LibraryFunctionLoad` command to load the `run_qubic` function.
 *
 *    Example Mathematica code:
 *    ```mathematica
 *    (* Load the library *)
 *    qubicRun = LibraryFunctionLoad["/path/to/your/compiled/library/qubic.so", "run_qubic", {"UTF8String", "UTF8String"}, "UTF8String"];
 *
 *    (* Define the input file path and options *)
 *    inputFile = "/path/to/your/data/example";
 *    options = "-k 10 -c 0.9 -o 5";
 *
 *    (* Call the function and get the results *)
 *    results = qubicRun[inputFile, options];
 *
 *    (* Print the results *)
 *    Print[results];
 *    ```
 */

// This function will parse the options string and set the parameters in the Prog_options struct.
void parse_options(const char* options_str) {
    std::stringstream ss(options_str);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, ' ')) {
        tokens.push_back(item);
    }

    po = new Prog_options;
    strcpy(po->FN, " ");
    strcpy(po->BN, " ");
    po->IS_DISCRETE = FALSE;
    po->COL_WIDTH = 3;
    po->DIVIDED = 1;
    po->QUANTILE = .06;
    po->TOLERANCE = 1;
    po->FP = NULL;
    po->FB = NULL;
    po->RPT_BLOCK = 100;
    po->SCH_BLOCK = 500;
    po->FILTER = 1;
    po->IS_SWITCH = FALSE;
    po->IS_cond = FALSE;
    po->IS_spearman = FALSE;
    po->IS_new_discrete = FALSE;
    po->IS_Fast = FALSE;
    po->IS_MaxMin = FALSE;
    po->IS_rpkm = FALSE;
    po->EM = 100;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "-q" && i + 1 < tokens.size()) {
            po->QUANTILE = std::stod(tokens[++i]);
        } else if (tokens[i] == "-r" && i + 1 < tokens.size()) {
            po->DIVIDED = std::stoi(tokens[++i]);
        } else if (tokens[i] == "-d") {
            po->IS_DISCRETE = TRUE;
        } else if (tokens[i] == "-f" && i + 1 < tokens.size()) {
            po->FILTER = std::stod(tokens[++i]);
        } else if (tokens[i] == "-k" && i + 1 < tokens.size()) {
            po->COL_WIDTH = std::stoi(tokens[++i]);
        } else if (tokens[i] == "-c" && i + 1 < tokens.size()) {
            po->TOLERANCE = std::stod(tokens[++i]);
        } else if (tokens[i] == "-o" && i + 1 < tokens.size()) {
            po->RPT_BLOCK = std::stoi(tokens[++i]);
            po->SCH_BLOCK = 5 * po->RPT_BLOCK;
        }
    }
}

extern "C" {
    const char* run_qubic(const char* input_file, const char* options_str) {
        static std::string result;
        std::stringstream output_stream;

        parse_options(options_str);
        strcpy(po->FN, input_file);
        po->FP = mustOpen(po->FN, "r");

        get_matrix_size(po->FP);
        genes_n = reinterpret_cast<char **>(alloc2c(rows, LABEL_LEN));
        conds_n = reinterpret_cast<char **>(alloc2c(cols, LABEL_LEN));

        read_labels(po->FP);

        if (po->IS_DISCRETE) {
            read_discrete(po->FP);
        } else {
            read_continuous(po->FP);
            char stream_nm[LABEL_LEN + 20];
            strcpy(stream_nm, po->FN);
            strcat(stream_nm, ".rules");
            if (po->IS_new_discrete) discretize_new(stream_nm);
            else if (po->IS_rpkm) discretize_rpkm(stream_nm);
            else discretize(stream_nm);
            for (auto row = 0; row < rows; row++) delete[] arr[row];
            delete[] arr;
        }
        fclose(po->FP);

        make_graph(output_stream);

        // Cleanup
        for (auto row = 0; row < rows; row++) delete[] arr_c[row];
        delete[] arr_c;
        for (auto row = 0; row < rows; row++) delete[] genes_n[row];
        delete[] genes_n;
        for (auto col = 0; col < cols; col++) delete[] conds_n[col];
        delete[] conds_n;
        delete po;
        delete[] sublist;
        delete[] symbols;

        result = output_stream.str();
        return result.c_str();
    }
}
