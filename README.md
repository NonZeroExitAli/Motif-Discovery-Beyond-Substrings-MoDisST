
# Motif Discovery Beyond Substrings (MoDisST): Implementing Suffix Tree for Motif Discovery in DNA/Protein Sequences
This research intends to uncover motifs within DNA or protein sequences in bioinformatics more rapidly by utilizing Ukkonen's suffix tree generation approach. This dependable method enables researchers to effectively examine big sequences, even with large datasets. The linear time complexity of this method makes it highly effective. The project also included complex data structures and algorithm optimization approaches, making it a useful resource for bioinformatics researchers and students.






### Prerequisites

```
C++ compiler (GCC, Clion, MSVC, etc.)
C++11 standard or later

```



### Features

- Constructs a suffix tree using Ukkonen's algorithm
- Finds the longest common substring (LCS) between two sequences
- Handles input and output through file operations
- The algorithm operates in linear time, making it efficient and optimized for large datasets.





### Installation and Usage

```
1- Download the source code files.
2- Prepare your input sequences in a file named seqs.txt in the same directory as main.cpp. The sequences should be in FASTA format.
3- Compile the source code using your preferred C++ compiler.
4- Run the executable.
5- View the output in LongestCommon.txt to see the longest common substring and its length.
```
    
### Code Explanation

- main.cpp
  ```
  Structures and Constants:
  - Node: Represents each node in the suffix tree.
  - MAX_CHAR: Maximum number of characters (256 for extended ASCII).
  ```

- Functions
```
   - newNode(start, *end): Creates a new node.
   - edgeLength(node): Computes the length of the edge for a given node.
   - walkDown(currNode): Adjusts active points during tree traversal.
   - extendSuffixTree(pos): Main function to extend the suffix tree with new suffixes.
   - setSuffixIndexByDFS(node, height): Sets the suffix indices using DFS.
   - buildSuffixTree(): Builds the suffix tree for the given text.
   - getLongestCommonSubstring(): Traverses the tree to find the longest common substring.
   - read_seqs(path): Reads sequences from a file.
   - prepare_seqs(lines): Prepares the sequences by concatenating them with separators.

```

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)


