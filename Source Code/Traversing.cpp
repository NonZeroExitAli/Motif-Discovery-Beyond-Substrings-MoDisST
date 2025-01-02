//
// Created by 3lolo on 5/18/2024.
//


#include <iostream>
#include <fstream>

#include "Building the tree.cpp"

//recursive function to traverse all the tree
int doTraversal(Node *n, int LH, int* maxH, int* stringstart) {
    if (n == NULL) //tha base case
        return 0;
    int result;
    if (n->suffixIndex < 0) { // check if it's an internal node
        for (int i = 0; i < MAX_CHAR; i++) {
            if (n->children[i] != NULL) { //check child is a parent of not
                result = doTraversal(n->children[i], LH + edgeLength(n->children[i]), maxH, stringstart);
                if (n->suffixIndex == -1)
                    n->suffixIndex = result;
                else if ((n->suffixIndex == -2 && result == -3) || (n->suffixIndex == -3 && result == -2) || n->suffixIndex == -4) { //the most important condition
                    n->suffixIndex = -4;
                    if (*maxH < LH) {
                        *maxH = LH;
                        *stringstart = *(n->end) - LH + 1;
                    }
                }
            }
        }
    } else if (n->suffixIndex < size1) {
        return -2; //from the first string
    } else if (n->suffixIndex >= size1) {
        return -3; //from the second string
    }
    return n->suffixIndex;
}


void getLongestCommonSubstring() {
    int maxHeight = 0;
    int stringstart = 0;
    doTraversal(root, 0, &maxHeight, &stringstart); // the maxHeight and stringstart passed by refrence to update their values here

    if (maxHeight == 0) {
        // Write "No common substring" to the file
        ofstream outputFile("longest_common_substring.txt");
        outputFile << "No common substring" << endl;
        outputFile.close();
    } else {
        string output = "";
        for (int k = 0; k < maxHeight; k++) {
            output += text[k + stringstart];
        }
        output += " with length= " + to_string(maxHeight) + "\n";

        // Write the output to the file
        ofstream outputFile("../longest_common_substring.txt");
        outputFile << output;
        outputFile.close();

        // Print the output to the console
        cout << output;
    }
}

// take the sequences as a vector of sequences
vector<string> read_seqs(const string &path) {
    vector<string> lines;
    ifstream myfile(path);
    string line;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            lines.push_back(line);
        }
    } else {
        cout << "Cannot open the file!!";
    }
    return lines;
}

//concatenate sequences in string with identifires
string prepare_seqs(const vector<string> &lines) {
    string input;
    bool skipFirstLine = true;
    for (const auto &line : lines) {
        if (!line.empty() && line[0] == '>') {
            if (skipFirstLine) {
                input += line.substr(1);
                skipFirstLine = false;
            } else {
                input += "#";
                input += line.substr(1);
            }
        } else {
            input += line;
        }
    }
    input += "$";
    return input;
}

int main() {
    string path = "../seqs2.txt";
    vector<string> lines = read_seqs(path);
    string preparedSeqs = prepare_seqs(lines);
    cout << preparedSeqs << endl;

    size1 = preparedSeqs.find('#') + 1; //seq len
    strcpy(text, preparedSeqs.c_str());
    buildSuffixTree();
    getLongestCommonSubstring();

}





