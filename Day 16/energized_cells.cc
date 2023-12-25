#include <iostream>
#include <queue>
#include <set>

namespace Day16 {

using ::std::cout;

class Maze {

public: // change it back to private
    std::vector<std::string>& grid;
    enum Direction {
        left = 0,
        right = 1,
        up = 2,
        down = 3
    };

    class Beam {
    public:
        std::pair<int,int> coordinates;
        Direction direction;
        Beam() {}
        Beam(std::pair<int,int> coord_in, Direction dir_in):
            coordinates(coord_in), direction(dir_in) {}
        bool operator<(const Beam& rhs) const {
            // return coordinates.first < rhs.coordinates.first;
            return std::tie(coordinates.first, coordinates.second, direction) < std::tie(rhs.coordinates.first, rhs.coordinates.second, rhs.direction);
        }
        bool operator=(const Beam& rhs) const {
            return coordinates.first == rhs.coordinates.first && 
                coordinates.second == rhs.coordinates.second && 
                direction == rhs.direction;
        }
        friend std::ostream& operator<<(std::ostream &strm, const Beam &beam) {
            return strm << "(" << beam.coordinates.first << "," 
                << beam.coordinates.second << ") " << beam.direction;
        }
    };

public: 
    Maze(std::vector<std::string>& grid_in) : grid(grid_in) {}

    // Return the number of cells through which at least one beam has passed.
    int getEnergizedCells() {
        std::queue<Beam> process;
        std::set<Beam> visited;
        process.push(Beam(std::make_pair(0, 0), right));
        
        while (!process.empty()) {
            Beam curr = process.front();
            process.pop();
            if (visited.find(curr) != visited.end()) {
                continue;
            }
            visited.insert(curr);
            // The current coordinate has already been processed, so remove it
            // from the queue, increment the counter, and figure out which other
            // coordinates are energized, and put all other coordinates into the 
            // queue. Also add the current coordinate into visited node.
            char gridChar = grid[curr.coordinates.first][curr.coordinates.second];
            if (gridChar == '\\' || gridChar == '/')
                ProcessMirror(curr, process, visited, gridChar);
            else if (gridChar == '-' || gridChar == '|')   
                ProcessSplitter(curr, process, visited, gridChar);
            // if its empty cell, you still have to move the beam in a given direction.
            else ProcessEmpty(curr, process, visited);
            // PrintQueue(process);
        }
        // PrintVisited(visited);
        return GetNumCoordinatesFromVisited(visited);
    }

private:
    void ProcessMirror(Beam curr, std::queue<Beam>& process, std::set<Beam>& visited, char gridCurr) {
        if (gridCurr == '\\') {
            if (curr.direction == right) {
                if (curr.coordinates.first+1 >= grid.size()) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first+1, curr.coordinates.second), down);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == left) {
                if (curr.coordinates.first-1 < 0) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first-1, curr.coordinates.second), up);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == up) {
                if (curr.coordinates.second-1 < 0) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second-1), left);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == down) {
                if (curr.coordinates.second+1 >= grid.at(0).size()) return;
                Beam newBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second+1), right);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
        } else { // gridCurr will be '\/' /
            if (curr.direction == right) {
                if (curr.coordinates.first-1 < 0) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first-1, curr.coordinates.second), up);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == left) {
                if (curr.coordinates.first+1 > grid.size()) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first+1, curr.coordinates.second), down);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == up) {
                if (curr.coordinates.second+1 >= grid.at(0).size()) return; // out of bounds
                Beam newBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second+1), right);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
            if (curr.direction == down) {
                if (curr.coordinates.second-1 < 0) return;
                Beam newBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second-1), left);
                if (visited.find(newBeam) == visited.end())
                    process.push(newBeam);
            }
        }
    }
    void ProcessSplitter(Beam curr, std::queue<Beam>& process, std::set<Beam>& visited, char gridCurr) {
        if (gridCurr == '-') {
            if (curr.direction == left || curr.direction == right) {
                ProcessEmpty(curr, process, visited); // do nothing
                return;
            }
            // else, the direction is up or down.
            if (curr.coordinates.second-1 < 0) {}
            else {
                Beam leftBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second-1), left);
                if (visited.find(leftBeam) == visited.end()) {
                    process.push(leftBeam);
                }
            }
            if (curr.coordinates.second+1 >= grid.at(0).size()) {} // out of bounds
            else {
                Beam rightBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second+1), right);
                if (visited.find(rightBeam) == visited.end()) {
                    process.push(rightBeam);
                }
            }
        }
        else if (gridCurr == '|') {
            if (curr.direction == up || curr.direction == down) {
                ProcessEmpty(curr, process, visited); // do nothing
                return;
            }
            // else, the direction is left or right.
            if (curr.coordinates.first-1 < 0) {} // out of bounds
            else {
                Beam upBeam(std::make_pair(curr.coordinates.first-1, curr.coordinates.second), up);
                if (visited.find(upBeam) == visited.end()) {
                    process.push(upBeam);
                }
            }
            if (curr.coordinates.first+1 >= grid.size()) {} // out of bounds
            else {
                Beam downBeam(std::make_pair(curr.coordinates.first+1, curr.coordinates.second), down);
                if (visited.find(downBeam) == visited.end())
                    process.push(downBeam);
            }
        }
    }

    void ProcessEmpty(Beam curr, std::queue<Beam>& process, std::set<Beam>& visited) {
        if (curr.direction == right) {
            if (curr.coordinates.second+1 >= grid.at(0).size()) return; // out of bounds
            Beam rightBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second+1), right);
            if (visited.find(rightBeam) == visited.end()) {
                process.push(rightBeam);
            }
        }
        if (curr.direction == left) {
            if (curr.coordinates.second-1 < 0) return; // out of bounds
            Beam leftBeam(std::make_pair(curr.coordinates.first, curr.coordinates.second-1), left);
            if (visited.find(leftBeam) == visited.end()) {
                process.push(leftBeam);
            }
        }
        if (curr.direction == up) {
            if (curr.coordinates.first-1 < 0) return; // out of bounds
            Beam upBeam(std::make_pair(curr.coordinates.first-1, curr.coordinates.second), up);
            if (visited.find(upBeam) == visited.end()) {
                process.push(upBeam);
            }
        }
        if (curr.direction == down) {
            if (curr.coordinates.first+1 >= grid.size()) return; // out of bounds
            Beam downBeam(std::make_pair(curr.coordinates.first+1, curr.coordinates.second), down);
            if (visited.find(downBeam) == visited.end()) {
                process.push(downBeam);
            }
        }
    }

    int GetNumCoordinatesFromVisited(std::set<Beam> beam) {
        std::set<std::pair<int,int>> coordinates;
        for (Beam b : beam) coordinates.insert(b.coordinates);
        return coordinates.size();
    }

    void PrintQueue(std::queue<Beam> process) {
        cout << "We're printing the visited Queue.\n";
        while (!process.empty()) {
            cout << process.front() << " ";
            process.pop();
        }
        cout << "Done \n";
    }

    void PrintVisited(std::set<Beam> visited) {
        cout << "We're printing the visited set.\n";
        for (Beam b : visited) {
            cout << b << " ";
        }
    }
};

} // namespace Maze