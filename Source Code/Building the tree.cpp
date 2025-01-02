//
// Created by Suhaila on 5/18/2024.
//

#include <string.h>
#include <stdlib.h>

#include <vector>
using namespace std;

#define MAX_CHAR 256

struct Node {
    Node *children[MAX_CHAR];
    Node *suffixLink;
    int start;
    int *end;
    int suffixIndex;
};


char text[10000]; // Increased size for larger input strings
Node *root = NULL;
Node *lastNewNode = NULL;
Node *activeNode = NULL;
int activeEdge = -1;
int activeLength = 0;
int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size = -1;
int size1 = 0;

Node *newNode(int start, int *end) {
    Node *node = (Node*) malloc(sizeof(Node));
    for (int i = 0; i < MAX_CHAR; i++) {
        node->children[i] = NULL;
    }
    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    return node;
}

int edgeLength(Node *n) {
    if (n == root) return 0;
    return *(n->end) - (n->start) + 1;
}

int walkDown(Node *currNode) {
    if (activeLength >= edgeLength(currNode)) {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) activeEdge = pos;

        if (activeNode->children[(unsigned char) text[activeEdge]] == NULL) {
            activeNode->children[(unsigned char) text[activeEdge]] = newNode(pos, &leafEnd);
            if (lastNewNode != NULL) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        } else {
            Node *next = activeNode->children[(unsigned char) text[activeEdge]];
            if (walkDown(next)) continue;

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode != NULL && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                activeLength++;
                break;
            }

            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[(unsigned char) text[next->start]] = split;

            split->children[(unsigned char) text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[(unsigned char) text[next->start]] = next;

            if (lastNewNode != NULL) lastNewNode->suffixLink = split;
            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
    }
}

void setSuffixIndexByDFS(Node *n, int labelHeight) {
    if (n == NULL) return;

    int leaf = 1;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (n->children[i] != NULL) {
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight + edgeLength(n->children[i]));
        }
    }
    if (leaf == 1) {
        n->suffixIndex = ::size - labelHeight; // Use the global variable 'size'
    }
}


void buildSuffixTree() {
    ::size = strlen(text);
    rootEnd = (int*) malloc(sizeof(int));
    *rootEnd = -1;
    root = newNode(-1, rootEnd);
    activeNode = root;
    for (int i = 0; i < ::size; i++) extendSuffixTree(i);
    setSuffixIndexByDFS(root, 0);
}

