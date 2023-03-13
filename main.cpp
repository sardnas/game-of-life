#include <iostream>
#include <stdlib.h> 
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

const int columns = 30;
const int rows = 30;

void delay() {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

vector<vector<bool>> initialGrid(int numberOfActiveCoordinates, vector<pair<int, int>>* trueCoordinates){
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
                if (x < 1 || x > rows) {
                    throw out_of_range("Invalid input.");
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
                if (x < 1 || x > columns) {
                    throw out_of_range("Invalid input.");
                }
                break;
            }
            catch (const std::exception& e) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }

        grid[x-1][y-1] = true;
        trueCoordinates->push_back(make_pair(x-1, y-1));
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
            } else{
                outputGrid.append("- ");
            }
        }
        outputGrid.append("\n");
    }
    
    return outputGrid;
}

// rules for game of life:
// stay a live if 2-3 live neighbours, otherwise dead
// born if a dead cell has exact 3 neighbours
vector<vector<bool>> calculateNewGrid(vector<vector<bool>> grid, vector<pair<int, int>>* trueCoordinates){
    vector<vector<bool>> newGrid(grid.size(), vector<bool>(grid[0].size(), false));
    vector<pair<int, int>> newTrueCoordinates;
    vector<pair<int, int>> deadCellsToCheck;
    int grid_width = grid[0].size();
    int grid_height = grid.size();

    int counter = 0;
    

    // check which of the live coordinates can keep living
    for (auto& p : *trueCoordinates) {
        int x = p.first;
        int y = p.second;

        int xm = (x-1 < 0 ? grid_width - 1: x-1);
        int ym = (y-1 < 0 ? grid_height - 1: y-1);
        int xp = (x+1 > grid_width - 1? 0 : x+1);
        int yp = (y+1 > grid_height - 1? 0 : y+1);

        if(grid[xm][ym]){
            counter++;
        }else if(!grid[xm][ym] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xm,ym)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xm, ym));
        }

        if(grid[xm][y]){
            counter++;
        }else if(!grid[xm][y] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xm,y)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xm, y));
        }

        if(grid[xm][yp]){
            counter++;
        }else if(!grid[xm][yp] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xm,yp)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xm, yp));
        }

        if(grid[x][yp]){
            counter++;
        }else if(!grid[x][yp] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(x,yp)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(x, yp));
        }

        if(grid[xp][yp]){
            counter++;
        }else if(!grid[xp][yp] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xp,yp)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xp, yp));
        }

        if(grid[xp][y]){
            counter++;
        }else if(!grid[xp][y] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xp,y)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xp, y));
        }

        if(grid[xp][ym]){
            counter++;
        }else if(!grid[xp][ym] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(xp,ym)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(xp, ym));
        }

        if(grid[x][ym]){
            counter++;
        }else if (!grid[x][ym] || find(deadCellsToCheck.begin(), deadCellsToCheck.end(), make_pair(x,ym)) == deadCellsToCheck.end()){
            deadCellsToCheck.push_back(make_pair(x, ym));
        }

        if(counter > 1 && counter < 4){
            newGrid[x][y] = true;
            if((find(newTrueCoordinates.begin(), newTrueCoordinates.end(), make_pair(x,y)) == newTrueCoordinates.end())){
                newTrueCoordinates.push_back(make_pair(x, y));
            }
        }

        counter = 0;
    }

    for (auto& p : deadCellsToCheck) {
        int x = p.first;
        int y = p.second;

        int xm = (x-1 < 0 ? grid_width - 1: x-1);
        int ym = (y-1 < 0 ? grid_height - 1: y-1);
        int xp = (x+1 > grid_width - 1? 0 : x+1);
        int yp = (y+1 > grid_height - 1? 0 : y+1);

        counter = 0;
        if(grid[xm][ym]){
            counter++;
        }

        if(grid[xm][y]){
            counter++;
        }

        if(grid[xm][yp]){
            counter++;
        }

        if(grid[x][yp]){
            counter++;
        }

        if(grid[xp][yp]){
            counter++;
        }

        if(grid[xp][y]){
            counter++;
        }

        if(grid[xp][ym]){
            counter++;
        }

        if(grid[x][ym]){
            counter++;
        }

        if(counter == 3){

            newGrid[x][y] = true;
            if((find(newTrueCoordinates.begin(), newTrueCoordinates.end(), make_pair(x,y)) == newTrueCoordinates.end())){
                newTrueCoordinates.push_back(make_pair(x, y));
            }
        }
    }

    // reset trueCoordinates to the new set of true coordinates
    trueCoordinates->clear();  
    *trueCoordinates = newTrueCoordinates;

    return newGrid;
}

vector<vector<bool>> defaultGrids(vector<pair<int, int>>* trueCoordinates){
    vector<vector<bool>> grid(rows, vector<bool>(columns, false));
    string input = "";
    int x = 0;
    int model = 0;

    while (true) {
        cout << "1. Glider\n2. Pulsar\n3. Toad\n4. Spaceship\nWhich pattern would you like to begin with (1,2,3,4)?: ";
        cin >> input;
        try {
            x = stoi(input);
            if (x < 1 || x > 4) {
                throw out_of_range("Invalid input.");
            }
            if(x == 1){
                grid[5][5] = true;
                grid[6][5] = true;
                grid[7][5] = true;
                grid[7][4] = true;
                grid[6][3] = true;
                trueCoordinates->push_back(make_pair(5,5));
                trueCoordinates->push_back(make_pair(6,5));
                trueCoordinates->push_back(make_pair(7,5));
                trueCoordinates->push_back(make_pair(7,4));
                trueCoordinates->push_back(make_pair(6,3));
            }
            if(x == 2){ // todo
                grid[5][5] = true;
                grid[6][5] = true;
                grid[7][5] = true;
                trueCoordinates->push_back(make_pair(5,5));
                trueCoordinates->push_back(make_pair(6,5));
                trueCoordinates->push_back(make_pair(7,5));
            }
            if(x == 3){ //todo
                grid[5][5] = true;
                grid[6][5] = true;
                grid[7][5] = true;
                trueCoordinates->push_back(make_pair(5,5));
                trueCoordinates->push_back(make_pair(6,5));
                trueCoordinates->push_back(make_pair(7,5));
            }
            if(x == 4){ //todo
                grid[5][5] = true;
                grid[6][5] = true;
                grid[7][5] = true;
                trueCoordinates->push_back(make_pair(5,5));
                trueCoordinates->push_back(make_pair(6,5));
                trueCoordinates->push_back(make_pair(7,5));
            }
            break;
        }
        catch (const std::exception& e) {
            cout << "Invalid input. Please enter a valid number." << endl;
        }
    }


    return grid;
}


int main() {
    vector<pair<int, int>> trueCoordinates;
    //int activeCoordinates = initialActiveCoordinates();
    vector<vector<bool>> grid = defaultGrids(&trueCoordinates);//initialGrid(activeCoordinates, &trueCoordinates);
    string outputGrid = getOutPutGrid(grid);
    vector<vector<bool>> newGrid;

    while(true){
        cout << " " << endl;
        cout << outputGrid;
        delay();
        newGrid = calculateNewGrid(grid, &trueCoordinates);
        if(grid == newGrid){
                break;
        }
        grid = newGrid;
        outputGrid = getOutPutGrid(grid);
    }

    return 0;
}