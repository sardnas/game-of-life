#include <iostream>
#include <stdlib.h> 
#include <map>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

const int columns = 15;
const int rows = 15;
vector<pair<int, int>> trueCoordinates;

void delay() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

vector<vector<bool>> initialGrid(int numberOfActiveCoordinates){
    vector<vector<bool>> grid(rows, vector<bool>(columns, false));
    string input = "";
    int x = 0;
    int y = 0;

    for(int i = 0; i < numberOfActiveCoordinates; i++){
        
        while (true) {
            cout << i + 1 << ". Enter the squares x coordinate: ";
            cin >> input;
            try {
                x = stoi(input);
                if (x < 1 || x > 15) {
                    throw out_of_range("Invalid input. Number must be between 1 and 15.");
                }
                break;
            }
            catch (const std::exception& e) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }

        while (true) {
            cout << i + 1 << ". Enter the squares y coordinate: ";
            cin >> input;
            try {
                y = stoi(input);
                if (x < 1 || x > 15) {
                    throw out_of_range("Invalid input. Number must be between 1 and 15.");
                }
                break;
            }
            catch (const std::exception& e) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }

        grid[x-1][y-1] = true;
    }

    return grid;
}

int initialActiveCoordinates(){
    int activeCoordinates = 0;
    string input = "";

    while (true) {
            cout << "Enter number of active squares to begin with (" << columns << "x" << rows << ") grid): ";
            cin >> input;
            try {
                activeCoordinates = stoi(input);
                break;
            }
            catch (const std::exception& e) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
    
    return activeCoordinates;
}

string getOutPutGrid(vector<vector<bool>> grid){
    string outputGrid = "";
    // Loop through the rows of the grid
    for (int i = 0; i < rows; i++) {
        // Loop through the columns of the grid
        for (int j = 0; j < columns; j++) {
            // Check if the value at the current position is true
            if (grid[i][j]) {
                outputGrid.append("O ");
                trueCoordinates.push_back(make_pair(i, j));
            } else{
                outputGrid.append("- ");
            }
        }
        outputGrid.append("\n");
    }
    
    return outputGrid;
}

vector<vector<bool>> calculateNewGrid(vector<vector<bool>> grid){
    vector<pair<int, int>> newTrueCoordinates;
    for (auto& p : trueCoordinates) {
        int x = p.first;
        int y = p.second;
        /*
        if(grid[][]){

        }
        */
    }

    return grid;
}

int main() {
    int activeCoordinates = initialActiveCoordinates();
    vector<vector<bool>> grid = initialGrid(activeCoordinates);
    string outputGrid = getOutPutGrid(grid);
    cout << outputGrid;
    delay();
    
    // function to calculate new grid, takes current grid and returns new grid

    return 0;
}