#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>

std::mutex fileMutex;       // For safe file access
std::mutex outputMutex;     // For safe output (if needed)

// Structure to hold chunk data
struct Chunk {
    std::vector<unsigned char> originalData;
    std::vector<unsigned char> compressedData;
};

// Simple RLE compression: [A,A,A] → [3,A]
void compressRLEChunk(Chunk &chunk) {
    const std::vector<unsigned char> &input = chunk.originalData;
    std::vector<unsigned char> &output = chunk.compressedData;

    size_t i = 0;
    while (i < input.size()) {
        unsigned char value = input[i];
        unsigned char count = 1;

        while ((i + count < input.size()) && (input[i + count] == value) && (count < 255)) {
            ++count;
        }

        output.push_back(count);
        output.push_back(value);
        i += count;
    }
}

int main() {
    std::string inputFile, outputFile;
    std::cout << "Enter input filename to compress: ";
    std::cin >> inputFile;
    std::cout << "Enter output compressed filename: ";
    std::cin >> outputFile;

    std::ifstream infile(inputFile, std::ios::binary);
    if (!infile) {
        std::cerr << "Error: Cannot open input file.\n";
        return 1;
    }

    infile.seekg(0, std::ios::end);
    size_t totalSize = infile.tellg();
    infile.seekg(0, std::ios::beg);

    const size_t threadCount = std::thread::hardware_concurrency();
    const size_t chunkSize = (totalSize + threadCount - 1) / threadCount;

    std::vector<Chunk> chunks(threadCount);

    for (size_t i = 0; i < threadCount; ++i) {
        size_t offset = i * chunkSize;
        if (offset >= totalSize) break;

        size_t sizeToRead = std::min(chunkSize, totalSize - offset);
        chunks[i].originalData.resize(sizeToRead);

        infile.seekg(offset, std::ios::beg);
        infile.read(reinterpret_cast<char *>(chunks[i].originalData.data()), sizeToRead);
    }

    infile.close();

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (auto &chunk : chunks) {
        threads.emplace_back(compressRLEChunk, std::ref(chunk));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Compression took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    std::ofstream outfile(outputFile, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error: Cannot open output file.\n";
        return 1;
    }

    // Write number of chunks
    size_t chunkCount = chunks.size();
    outfile.write(reinterpret_cast<char *>(&chunkCount), sizeof(chunkCount));

    // Write metadata and compressed content
    for (const auto &chunk : chunks) {
        size_t originalSize = chunk.originalData.size();
        size_t compressedSize = chunk.compressedData.size();
        outfile.write(reinterpret_cast<const char *>(&originalSize), sizeof(originalSize));
        outfile.write(reinterpret_cast<const char *>(&compressedSize), sizeof(compressedSize));
        outfile.write(reinterpret_cast<const char *>(chunk.compressedData.data()), compressedSize);
    }

    outfile.close();

    // Report size and ratio
    std::ifstream result(outputFile, std::ios::binary | std::ios::ate);
    std::streamsize compressedSize = result.tellg();
    result.close();

    std::cout << "Original file size: " << totalSize << " bytes\n";
    std::cout << "Compressed file size: " << compressedSize << " bytes\n";

    double ratio = 100.0 * (1.0 - static_cast<double>(compressedSize) / totalSize);
    std::cout << "Compression ratio: " << ratio << "%\n";

    std::cout << "Compression complete. Output saved to " << outputFile << std::endl;
    return 0;
}
