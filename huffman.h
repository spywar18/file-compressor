#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>
#include <cstddef>

// Node structure for Huffman Tree
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;
    
    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    Node(int freq) : character('\0'), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue (min-heap based on frequency)
struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->frequency == b->frequency) {
            return a->character > b->character; // For consistent ordering
        }
        return a->frequency > b->frequency;
    }
};

class HuffmanCoding {
private:
    Node* root;
    std::unordered_map<char, std::string> codes;
    std::unordered_map<char, int> frequency;
    
    void generateCodes(Node* node, std::string code);
    void deleteTree(Node* node);
    std::string decode(const std::string& encodedText, Node* root);
    
public:
    HuffmanCoding();
    ~HuffmanCoding();
    
    void buildFrequencyTable(const std::string& text);
    void buildHuffmanTree();
    void displayFrequencyTable();
    void displayCodes();
    std::string encode(const std::string& text);
    std::string decode(const std::string& encodedText);
    void compressFile(const std::string& inputFile, const std::string& outputFile);
    void decompressFile(const std::string& compressedFile, const std::string& outputFile);
    double getCompressionRatio(const std::string& original, const std::string& compressed);
};

#endif