#include "huffman.h"
#include <iterator>

HuffmanCoding::HuffmanCoding() : root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    deleteTree(root);
}

void HuffmanCoding::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void HuffmanCoding::buildFrequencyTable(const std::string& text) {
    frequency.clear();
    for (int i = 0; i < (int)text.length(); ++i) {
        char ch = text[i];
        frequency[ch]++;
    }
}

void HuffmanCoding::buildHuffmanTree() {
    if (frequency.empty()) {
        std::cout << "No data to build tree!" << std::endl;
        return;
    }
    
    // Special case: only one unique character
    if (frequency.size() == 1) {
        char ch = frequency.begin()->first;
        root = new Node(ch, frequency[ch]);
        codes[ch] = "0";
        return;
    }
    
    // Create priority queue (min-heap)
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    
    // Create leaf nodes and add to priority queue
    for (auto& pair : frequency) {
        pq.push(new Node(pair.first, pair.second));
    }
    
    // Build Huffman tree
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        Node* merged = new Node(left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    root = pq.top();
    codes.clear();
    generateCodes(root, "");
}

void HuffmanCoding::generateCodes(Node* node, std::string code) {
    if (!node) return;
    
    // Leaf node - store the code
    if (!node->left && !node->right) {
        codes[node->character] = code.empty() ? "0" : code;
        return;
    }
    
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCoding::displayFrequencyTable() {
    std::cout << "\n=== FREQUENCY TABLE ===" << std::endl;
    std::cout << "Character\tFrequency" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    for (auto& pair : frequency) {
        char ch = pair.first;
        if (ch == ' ') {
            std::cout << "[SPACE]";
        } else if (ch == '\n') {
            std::cout << "[NEWLINE]";
        } else if (ch == '\t') {
            std::cout << "[TAB]";
        } else {
            std::cout << ch;
        }
        std::cout << "\t\t" << pair.second << std::endl;
    }
}

void HuffmanCoding::displayCodes() {
    std::cout << "\n=== HUFFMAN CODES ===" << std::endl;
    std::cout << "Character\tCode" << std::endl;
    std::cout << "-------------------" << std::endl;
    
    for (auto& pair : codes) {
        char ch = pair.first;
        if (ch == ' ') {
            std::cout << "[SPACE]";
        } else if (ch == '\n') {
            std::cout << "[NEWLINE]";
        } else if (ch == '\t') {
            std::cout << "[TAB]";
        } else {
            std::cout << ch;
        }
        std::cout << "\t\t" << pair.second << std::endl;
    }
}

std::string HuffmanCoding::encode(const std::string& text) {
    if (codes.empty()) {
        std::cout << "No Huffman codes available. Build tree first!" << std::endl;
        return "";
    }
    
    std::string encoded = "";
    for (char ch : text) {
        if (codes.find(ch) != codes.end()) {
            encoded += codes[ch];
        } else {
            std::cout << "Warning: Character '" << ch << "' not found in codes!" << std::endl;
        }
    }
    return encoded;
}

std::string HuffmanCoding::decode(const std::string& encodedText) {
    return decode(encodedText, root);
}

std::string HuffmanCoding::decode(const std::string& encodedText, Node* root) {
    if (!root || encodedText.empty()) {
        return "";
    }
    
    // Special case: only one unique character
    if (!root->left && !root->right) {
        return std::string(encodedText.length(), root->character);
    }
    
    std::string decoded = "";
    Node* current = root;
    
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            std::cout << "Invalid bit in encoded text: " << bit << std::endl;
            return "";
        }
        
        // Reached leaf node
        if (!current->left && !current->right) {
            decoded += current->character;
            current = root; // Reset to root for next character
        }
    }
    
    return decoded;
}

void HuffmanCoding::compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open input file: " << inputFile << std::endl;
        return;
    }
    
    // Read entire file content
    std::string content((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());
    inFile.close();
    
    if (content.empty()) {
        std::cout << "Error: Input file is empty!" << std::endl;
        return;
    }
    
    // Build frequency table and Huffman tree
    buildFrequencyTable(content);
    buildHuffmanTree();
    
    // Encode the content
    std::string encoded = encode(content);
    
    // Write compressed data to file
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not create output file: " << outputFile << std::endl;
        return;
    }
    
    outFile << encoded;
    outFile.close();
    
    std::cout << "File compressed successfully!" << std::endl;
    std::cout << "Original size: " << content.length() << " characters" << std::endl;
    std::cout << "Compressed size: " << encoded.length() << " bits" << std::endl;
    std::cout << "Compression ratio: " << getCompressionRatio(content, encoded) << "%" << std::endl;
}

void HuffmanCoding::decompressFile(const std::string& compressedFile, const std::string& outputFile) {
    std::ifstream inFile(compressedFile);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open compressed file: " << compressedFile << std::endl;
        return;
    }
    
    std::string encoded((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());
    inFile.close();
    
    if (encoded.empty()) {
        std::cout << "Error: Compressed file is empty!" << std::endl;
        return;
    }
    
    // Decode the content
    std::string decoded = decode(encoded);
    
    // Write decompressed data to file
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not create output file: " << outputFile << std::endl;
        return;
    }
    
    outFile << decoded;
    outFile.close();
    
    std::cout << "File decompressed successfully!" << std::endl;
}

double HuffmanCoding::getCompressionRatio(const std::string& original, const std::string& compressed) {
    if (original.empty()) return 0.0;
    
    double originalBits = original.length() * 8; // 8 bits per character
    double compressedBits = compressed.length(); // Already in bits
    
    return ((originalBits - compressedBits) / originalBits) * 100.0;
}