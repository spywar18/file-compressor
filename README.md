# 🗜️ Huffman Coding File Compressor

[![Live Demo](https://img.shields.io/badge/Live-Demo-brightgreen?style=for-the-badge)](https://spywar18.github.io/file-compressor/)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](LICENSE)
[![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)

> Interactive web-based implementation of Huffman Coding algorithm for lossless data compression with real-time analysis and visualizations.

## 🚀 [Live Demo](https://spywar18.github.io/file-compressor/)

## 🔍 What is Huffman Coding?

Huffman Coding is a **lossless data compression algorithm** that assigns variable-length binary codes to characters based on their frequency. More frequent characters get shorter codes, less frequent ones get longer codes, achieving optimal compression.

**Example:**
```
Text: "hello world"
'l' appears 3 times → gets code "00" (2 bits)
'h' appears 1 time → gets code "1000" (4 bits)

Original: 88 bits (11 chars × 8 bits)
Compressed: ~32 bits
Compression: 64% space saved
```

## ✨ Features

- 📊 **Real-time Compression** - Instant results as you type
- 📁 **File Upload Support** - Compress text files directly  
- 📈 **Detailed Analysis** - Frequency tables and compression statistics
- 💾 **Download Results** - Export compressed data
- 📱 **Responsive Design** - Works on all devices
- 🎓 **Educational** - Perfect for learning algorithms

## 🧮 How the Algorithm Works

### Step 1: Count Character Frequencies
```
Input: "aabbc"
Frequencies: a=2, b=2, c=1
```

### Step 2: Build Huffman Tree
1. Create nodes for each character with their frequencies
2. Repeatedly merge two nodes with lowest frequencies
3. Continue until single root node remains

### Step 3: Generate Codes
Traverse tree assigning '0' for left, '1' for right:
```
Final codes:
'a' → "0"
'b' → "10" 
'c' → "11"
```

### Step 4: Encode/Decode
```
"aabbc" → "001010111" (9 bits vs 40 bits original)
Compression ratio: 77.5%
```

## 🎯 Usage Guide

1. **Enter Text**: Type or upload a text file
2. **Click Compress**: Algorithm runs automatically
3. **View Analysis**: Check frequency table and compression stats
4. **Download**: Export compressed binary data
5. **Decompress**: Verify perfect reconstruction

## 📊 Performance

```
| Text Type | Typical Compression |
|-----------|-------------------|
| English Text | 40-60% |
| Code Files | 30-50% |
| Repeated Patterns | 60-80% |
| Random Data | 0-10% |
```

**Time Complexity:** O(n log k) where n = text length, k = unique characters

## 💻 Technical Details

- **Pure JavaScript** - No external dependencies
- **Client-side Processing** - All computation in browser
- **Modern Web APIs** - File API, Blob API for file handling
- **Cross-browser Compatible** - Works in all modern browsers

### Core Implementation
```javascript
class HuffmanCoding {
    buildFrequencyTable(text) { /* Count characters */ }
    buildHuffmanTree() { /* Create binary tree */ }
    generateCodes(node, code) { /* Assign binary codes */ }
    encode(text) { /* Convert to binary */ }
    decode(encodedText) { /* Reconstruct original */ }
}
```

## 🎓 Educational Value

Perfect for learning:
- **Data Structures**: Binary trees, priority queues, hash maps
- **Algorithms**: Greedy algorithms and optimality proofs
- **Information Theory**: Entropy, optimal coding, compression limits
- **Complexity Analysis**: Time and space complexity


**🚀 [Try the live demo](https://spywar18.github.io/file-compressor/) now!**