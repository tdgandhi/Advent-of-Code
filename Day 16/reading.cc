#include <string>
#include <fstream>
#include <iostream>

namespace Day16 {

class MatrixReader {
private:
  std::string filename;
  std::vector<std::string> lines;

public:
  // Constructor takes one string argument and assigns it to both private members.
    MatrixReader(const std::string_view& filename) : filename(filename) {
        lines = getFileInLinesForm(filename);
    }

    // This function reads the file of the format defined in 
    // day 16 of advent of code from the given *pathname* and 
    // returns a temp version of it.
    std::vector<std::string> getFileInLinesForm(std::string_view filename) {
        std::string filePath(filename);
        std::vector<std::string> tempVector;
        // Open the file
        std::ifstream file(filePath);

        // Check if the file opened successfully
        if (!file.is_open()) {
            std::cout << "Error opening file: " << filePath << std::endl;
            return tempVector;
        }

        // Read the file line by line
        std::string line;
        while (std::getline(file, line)) {
            // Process the line here (e.g., print it, store it in a vector)
            tempVector.push_back(line);
        }

        // Close the file
        file.close();
        return tempVector;
    }

    // Returns a matrix with the 2D grid containing mirrors and splitters
    std::vector<std::string> getMatrix() {
        return lines;
    }
};

} // namespace Day16