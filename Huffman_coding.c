#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

// A structure to represent a node in the Huffman tree
struct Node {
    char data;
    int freq;
    struct Node *left, *right;
};

// A utility function to allocate a new node
struct Node* newNode(char data, int freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to sort the nodes by frequency in ascending order
void sortNodes(struct Node* nodes[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (nodes[i]->freq > nodes[j]->freq) {
                struct Node* temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }
}

// Combine two nodes to create a new parent node
struct Node* combineNodes(struct Node* left, struct Node* right) {
    struct Node* parent = newNode('$', left->freq + right->freq);
    parent->left = left;
    parent->right = right;
    return parent;
}

// Print Huffman codes from the root of the Huffman Tree and calculate total bits
void printCodes(struct Node* root, int arr[], int top, int* totalBits) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, totalBits);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, totalBits);
    }

    if (!root->left && !root->right) {
        // Print the character, its frequency, the Huffman code, and bits used
        printf("%c\t%d\t", root->data, root->freq);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\t%d\n", root->freq * top);

        // Calculate the total number of bits used by this character
        *totalBits += root->freq * top;
    }
}

// Build the Huffman Tree using a sorting method instead of a heap
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node* nodes[MAX];
    
    // Step 1: Create a node for each character and store it in an array
    for (int i = 0; i < size; i++) {
        nodes[i] = newNode(data[i], freq[i]);
    }

    // Step 2: Sort the nodes by frequency
    sortNodes(nodes, size);

    // Step 3: Build the Huffman Tree by combining the two smallest nodes until one node remains
    while (size > 1) {
        struct Node* left = nodes[0];  // Node with smallest frequency
        struct Node* right = nodes[1];  // Node with second smallest frequency

        // Create a new internal node that combines the two nodes
        struct Node* parent = combineNodes(left, right);

        // Remove the first two nodes and insert the new node
        for (int i = 2; i < size; i++) {
            nodes[i - 2] = nodes[i];
        }
        nodes[size - 2] = parent;
        size--;

        // Re-sort the array after adding the new node
        sortNodes(nodes, size);
    }

    // The remaining node is the root of the Huffman Tree
    return nodes[0];
}

// Count frequencies of characters in the message
void countFrequencies(char* str, char* chars, int* freq, int* size) {
    int len = strlen(str);
    int count[MAX] = {0};

    for (int i = 0; i < len; i++) {
        count[(int)str[i]]++;
    }

    int idx = 0;
    for (int i = 0; i < MAX; i++) {
        if (count[i] > 0) {
            chars[idx] = (char)i;
            freq[idx] = count[i];
            idx++;
        }
    }
    *size = idx;
}

int main() {
    char message[1000];
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove newline character

    // Calculate the total size of the message in bits (ASCII - 8 bits per character)
    int totalSizeOriginal = strlen(message) * 8;
    printf("\nTotal size of the original message: %d bits\n", totalSizeOriginal);

    char chars[MAX];
    int freq[MAX];
    int size;

    // Step 1: Count the frequency of each character in the message
    countFrequencies(message, chars, freq, &size);

    // Output the character frequencies
    printf("\nCharacter frequencies:\n");
    for (int i = 0; i < size; i++) {
        printf("%c: %d\n", chars[i], freq[i]);
    }

    // Step 2: Build the Huffman Tree
    struct Node* root = buildHuffmanTree(chars, freq, size);

    // Step 3: Print the Huffman Codes and calculate total bits
    int arr[MAX], top = 0;
    int totalBitsHuffman = 0;
    printf("\nChar\tFreq\tCode\tBits\n");
    printCodes(root, arr, top, &totalBitsHuffman);

    // Step 4: Output the total size for sending the message using Huffman coding
    printf("\nTotal bits used for the message (Huffman Coding): %d bits\n", totalBitsHuffman);
    printf("Total size for sending the message : %d bits\n", totalBitsHuffman + totalSizeOriginal);
    return 0;
}
