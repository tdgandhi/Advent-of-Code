
#include <iostream>
#include <set>

#include "reading.cc"
#include "energized_cells.cc"

int main() {
    Day16::Maze::Beam beam1;
    beam1.coordinates = std::make_pair(0,0);
    beam1.direction = Day16::Maze::right;

    Day16::Maze::Beam beam2;
    beam2.coordinates = std::make_pair(0,1);
    beam2.direction = Day16::Maze::down;

    std::cout << beam1;
    std::cout << beam2;

    std::set<Day16::Maze::Beam> set;

}