#include "huffman.h"

void displayMenu() {
    std::cout << "\n=== HUFFMAN CODING FILE COMPRESSOR ===" << std::endl;
    std::cout << "1. Compress a text string" << std::endl;
    std::cout << "2. Compress a file" << std::endl;
    std::cout << "3. Decompress a file" << std::endl;
    std::cout << "4. Demo with sample text" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

void demoCompression() {
    std::cout << "\n=== DEMO: HUFFMAN CODING ===" << std::endl;    
    std::string text = "hello world! this is a sample text for huffman compression.";
    std::cout << "Original text: \"" << text << "\"" << std::endl;
    std::cout << "Original length: " << text.length() << " characters" << std::endl;
    
    HuffmanCoding huffman;
    
    // Build frequency table and tree
    huffman.buildFrequencyTable(text);
    huffman.buildHuffmanTree();
    
    // Display analysis
    huffman.displayFrequencyTable();
    huffman.displayCodes();
    
    // Encode
    std::string encoded = huffman.encode(text);
    std::cout << "\nEncoded text: " << encoded << std::endl;
    std::cout << "Encoded length: " << encoded.length() << " bits" << std::endl;
    
    // Decode
    std::string decoded = huffman.decode(encoded);
    std::cout << "\nDecoded text: \"" << decoded << "\"" << std::endl;
    
    // Verify
    if (text == decoded) {
        std::cout << "✅ SUCCESS: Decoded text matches original!" << std::endl;
    } else {
        std::cout << "❌ ERROR: Decoded text doesn't match original!" << std::endl;
    }
    // Compression ratio
    double ratio = huffman.getCompressionRatio(text, encoded);
    std::cout << "\nCompression Statistics:" << std::endl;
    std::cout << "Original size: " << text.length() * 8 << " bits" << std::endl;
    std::cout << "Compressed size: " << encoded.length() << " bits" << std::endl;
    std::cout << "Compression ratio: " << ratio << "%" << std::endl;
}
void compressString() {
    std::cout << "\n=== STRING COMPRESSION ===" << std::endl;
    std::cout << "Enter text to compress: ";
    std::cin.ignore(); // Clear input buffer
    
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) {
        std::cout << "Error: Empty input!" << std::endl;
        return;
    }
    
    HuffmanCoding huffman;
    huffman.buildFrequencyTable(input);
    huffman.buildHuffmanTree();
    
    huffman.displayFrequencyTable();
    huffman.displayCodes();
    
    std::string encoded = huffman.encode(input);
    std::cout << "\nOriginal: \"" << input << "\"" << std::endl;
    std::cout << "Encoded:  " << encoded << std::endl;
    std::cout << "Decoded:  \"" << huffman.decode(encoded) << "\"" << std::endl;
    std::cout << "Compression ratio: " << huffman.getCompressionRatio(input, encoded) << "%" << std::endl;
}

void compressFile() {
    std::cout << "\n=== FILE COMPRESSION ===" << std::endl;
    std::string inputFile, outputFile;
    
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    
    std::cout << "Enter output file name for compressed data: ";
    std::cin >> outputFile;
    
    HuffmanCoding huffman;
    huffman.compressFile(inputFile, outputFile);
    
    // Display the codes used
    huffman.displayFrequencyTable();
    huffman.displayCodes();
}

void decompressFile() {
    std::cout << "\n=== FILE DECOMPRESSION ===" << std::endl;
    std::string compressedFile, outputFile;
    
    std::cout << "Enter compressed file name: ";
    std::cin >> compressedFile;
    
    std::cout << "Enter output file name for decompressed data: ";
    std::cin >> outputFile;
    
    // Note: In a real implementation, you'd need to store the tree structure
    // with the compressed file to be able to decompress it later.
    // For this demo, we assume the tree is still in memory.
    
    std::cout << "Note: This demo assumes the Huffman tree is still in memory." << std::endl;
    std::cout << "In a complete implementation, the tree structure would be saved with the compressed file." << std::endl;
}

int main() {
    int choice;
    
    std::cout << "Welcome to Huffman Coding File Compressor!" << std::endl;
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                compressString();
                break;
            case 2:
                compressFile();
                break;
            case 3:
                decompressFile();
                break;
            case 4:
                demoCompression();
                break;
            case 5:
                std::cout << "Thank you for using Huffman Coding Compressor!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice! Please enter 1-5." << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return 0;
}