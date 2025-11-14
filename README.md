# dd-project1 

This project implements the Quine–McCluskey (QM) algorithm for Boolean logic minimization.
It processes minterms and optional don’t-care terms to generate a minimized expression using Prime Implicants (PI) and Essential Prime Implicants (EPI).

🚀 Features

Full Quine–McCluskey grouping and merging

Prime Implicant generation

Essential Prime Implicant detection

Don’t-care support

Input validation: malformed lines, missing terms, out-of-range minterms

📁 Codebase Overview

QM.cpp — Core algorithm implementation

QM.h — Class definitions + helper functions

main.cpp — CLI entry point

Sample input files covering:

Inputs where all terms are PIs

Inputs with no EPIs

Inputs where PIs = EPIs

Variable sizes (4–20 bits)

Minterms out of range

Missing minterm or maxterm entries

🧱 Build Instructions

▶️ How to Run


The program loads the appropriate sample input file and prints:
• All PIs
• All EPIs
• All minimized Boolean expressions

📘 Algorithm Summary

Convert minterms/don’t-cares into binary

Group terms by number of 1s

Iteratively combine terms differing in one bit

Generate all Prime Implicants

Build the PI coverage table

Detect all Essential Prime Implicants

Produce the final minimized Boolean expression

🗂️ Repository Structure
dd-project1-main/
│── QM.cpp
│── QM.h
│── main.cpp
│── README.md
└── <input test files>

🔧 Function Descriptions (Brief)

QM(int s, string v1, string v2)
→ Converts minterms/don’t-cares into binary and initializes the algorithm.

~QM()
→ Cleans internal containers.

convert_max_to_min(string line)
→ Converts maxterms into their minterm equivalents.

createFirstColumn(vector<vector<string>>& groups)
→ Groups terms by number of 1s for the first QM table.

combineMinterms(term1, term2)
→ Combines terms differing in exactly one bit.

generatePI()
→ Generates all Prime Implicants.

generateEPI()
→ Finds all Essential Prime Implicants.

columnDominance()
→ Removes redundant minterm columns.

rowDominance()
→ Removes redundant PI rows.

recursiveSearch(...)
→ Recursive Search to find all minimal PI combinations.

generateSolutions()
→ Full solution: EPIs + dominance simplification + recursive search.

displayPI()
→ Prints Prime Implicants.

displayEPI()
→ Prints Essential Prime Implicants.

displaySolutions()
→ Prints minimized Boolean expressions.

isCovered(minterm, pi)
→ Checks if a PI covers a minterm.

generateVerilog(vector<string>)
→ Prints minimized logic as Verilog assign syntax.

// Note: I used chatgpt to beautify the readme file