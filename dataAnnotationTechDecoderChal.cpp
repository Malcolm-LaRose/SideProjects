// Data annotation tech coding exercise 1

// Malcolm LaRose 4/15/2024

// Using C++ 14 with VS Community

#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>



std::vector<int> genSeq(int n) { // Generates rhs of pyramid
	std::vector<int> outputVector;
	outputVector.push_back(1); // First member of sequence is 1
	for (int i = 1; i <= n; i++) {
		int seq_i = outputVector[i - 1] + (i + 1); // Following members
		outputVector.push_back(seq_i);
	}

	return outputVector; 
}


std::unordered_map<int, std::string> readTextFile(const std::string& filename) {
    std::unordered_map<int, std::string> dataMap;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            int number;
            std::string value;
            if (std::istringstream(line) >> number >> value) {
                dataMap[number] = value;
            }
            //else {
            //    std::cerr << "Error parsing line: " << line << std::endl;
            //}
        }
        file.close();
    }
    //else {
    //    std::cerr << "Unable to open file: " << filename << std::endl;
    //}

    return dataMap;
}

std::vector<std::string> decodeMap(std::unordered_map<int, std::string> data, std::vector<int> sequ) {
    std::vector<std::string> outputVector;
    for (size_t i = 0; i < sequ.size(); i += 2) {
        int num = sequ[i];
        std::string word = data[num];
        outputVector.push_back(word);
    }
    return outputVector;
}




void codingChallenge() {
    std::vector<int> res = genSeq(23);

    /*for (int n : res) {
        std::cout << n << ", ";
    }*/

    std::unordered_map<int, std::string> dataList = readTextFile("coding_qual_input.txt");

    //for (const auto& n : dataList) {
    //    std::cout << n.second << ", ";
    //}

    std::vector<std::string> partiallyDecodedMessage = decodeMap(dataList, res);

    for (const auto& n : partiallyDecodedMessage) {
    std::cout << n << " ";
    }


    
}


int main() {

    codingChallenge();

	return 0;
}

