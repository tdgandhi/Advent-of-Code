
#include <iostream>

#include "reading.cc"
#include "energized_cells.cc"

int readFileTest(std::string_view filename) {
	Day16::MatrixReader reader(filename);
	std::vector<std::string> matrix = reader.getMatrix();
	for (std::string line : matrix) {
		std::cout << line << "\n";
	}
	return 1;
}

int main(int argc, char* argv[]) {
	std::string_view filename = "./day16_file.txt";
	if (false) // set this to true if you want to print the contents of file as well.
		readFileTest(filename);
	Day16::MatrixReader reader(filename);
	std::vector<std::string> matrix = reader.getMatrix();
	std::cout << "Size of the matrix: " << matrix.size() << " x " << matrix.at(0).size() << "\n";
	Day16::Maze maze(matrix);
	std::cout << "Number of Enegrized cells: " << maze.getEnergizedCellsFromTopLeft();
	std::cout << "Max number of energized cells possible: " << maze.getMaxPossibleEnergizedCells();
	return 0;
}