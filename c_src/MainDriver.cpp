#include <iostream>
#include <set>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std;

#include "Coord2D.h"
#include "Tile.h"
#include "Path.h"
#include "Grid2D.h"
#include "GameGrid2D.h"
//#include "Hash.h"

void testGenerateGameGrid(int numOfGrids) {
    if(numOfGrids < 0) {
        cout << "You tried to generate a negative number of grids" << endl;
        exit(1);
    }

    Coord2D gridDimensions = Coord2D(50,50);
    for(int i = 0; i < numOfGrids; ++i) {
        try
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(19));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        GameGrid2D grid = GameGrid2D(gridDimensions, 5, 7);
        cout << "Grid #" << i << "\n" << grid.toString() << "\n" << endl;
    }
}


//NOTE: note using iterators in the c++ imp

// void testIterator() {
//     Coord2D gridDimensions = Coord2D(50,50);
//     Grid2D grid2D = Grid2D(gridDimensions);

//     set<Tile> tiles;
//     tiles.insert(*grid2D.getTile(Coord2D(0,0)));
//     // for (Tile t : grid) {
//     //     tiles.insert(t);
//     // }

//     for(unsigned int i = 0; i < grid2D.grid->size(); ++i) {
//         for(unsigned j = 0; j < grid2D.grid->at(i).size();++j) {
//             Tile* tempTile = grid2D.grid->at(i).at(j);
//             tiles.insert(*tempTile);
//         }
//     }

//     cout << "Expected size: " << gridDimensions.first*gridDimensions.second << endl;
//     cout << "Num of tiles: " << tiles.size() << endl;
// }

void testPaths() {
    Grid2D grid = Grid2D(Coord2D(50,50));
    cout << "Empty grid: \n\n" << grid.toString() << endl;

    Path path = Path(&grid);
    assert(path.addJoint(Coord2D(10,1)));
    assert(path.addJoint(Coord2D(10, 2)));
    assert(path.addJoint(Coord2D(30, 2)));
    assert(path.addJoint(Coord2D(30, 0)));

    path.setPathType(Tile::TileType::TRAVERSABLE, true);

    Grid2D copy = Grid2D(grid);
    copy.setTile(Tile::TileType::TRAVERSABLE, Coord2D(0,0));

    cout << "Populated grid:\n\n" << grid.toString() << endl;
    cout << "Copy:\n\n" << copy.toString() << endl;
}

void testMarkRect() {
    Coord2D gridDimensions = Coord2D(7,13);
    Grid2D grid = Grid2D(gridDimensions);

    cout << "Empty grid:\n" << grid.toString() << endl;

    Coord2D middleBand_lowLeft = Coord2D(0,3);
    Coord2D middleBand_upRight = Coord2D(gridDimensions.first-1, 6);

    cout << "Marking a band in the middle:" <<endl;
    grid.markRect(middleBand_lowLeft, middleBand_upRight, true);

    cout << grid.toString() << endl;
}

void testMarkRow() {
    Coord2D gridDimensions = Coord2D(10,10);
    Grid2D grid = Grid2D(gridDimensions);

    cout << "Empty grid:\n" << grid.toString() <<endl;

    Coord2D lowbar_left = Coord2D(0,2);
    Coord2D lowbar_right = Coord2D(gridDimensions.first-1, lowbar_left.second);

    cout << "Marking lower bar..." <<endl;
    grid.setTypeLine(lowbar_left, lowbar_right, Tile::TileType::TRAVERSABLE, 0,true);
    cout << grid.toString() <<endl;

    Coord2D vertbar_down = Coord2D(2,0);
    Coord2D vertbar_up = Coord2D(vertbar_down.first, gridDimensions.second-1);

    cout << "Marking vert bar..." << endl;
    grid.setTypeLine(vertbar_down, vertbar_up, Tile::TileType::TRAVERSABLE,2,true);
    cout << grid.toString() <<endl;
}

void testGrid() {
    Coord2D gridDimensions = Coord2D(7,13);
    Coord2D testPoint = Coord2D(0,gridDimensions.second-1);
    Coord2D emptyPoint = Coord2D(3,10);
    //Coord2D failPoint = Coord2D(7,14);

    Grid2D grid = Grid2D(gridDimensions);
    grid.setTile(Tile::TileType::TRAVERSABLE, testPoint);

    cout << grid.toString() << endl;
    cout << "Tile at " << testPoint << ": " << grid.getTile(testPoint) << endl;
    cout << "Tile at " << emptyPoint << ": " << grid.getTile(emptyPoint) << endl;

    cout << "Can testPoint go up? " << (grid.canGoUp(testPoint) ? "true" : "false") << endl;
    cout << "Can testPoint go down? " << (grid.canGoDown(testPoint) ? "true" : "false") << endl;
    cout << "Can testPoint go left? " << (grid.canGoLeft(testPoint) ? "true" : "false") << endl;
    cout << "Can testPoint go right? " << (grid.canGoRight(testPoint) ? "true" : "false") << endl;

    cout << "Getting the up of testPoint:" << grid.getUp(testPoint)->toString() << endl;
    cout << "Getting testPoint manually:" << grid.getTile(testPoint)->toString() <<endl;

    cout << grid.toString() << endl;
}

void testSetOfPoints() {
    Coord2D original = Coord2D(3,4);
    Coord2D duplicate = Coord2D(original);
    Coord2D anotherone = Coord2D(6,9);

    assert(&original != &duplicate);
    assert(duplicate == original);

    // set<Coord2D,Coord2DHasher,Coord2DComparator> set = set<Coord2D>(3);
    set<Coord2D> coordSet;
    coordSet.insert(original);
    cout << "Set contains original. Contains duplicate? " << ((coordSet.find(duplicate) == coordSet.end()) ? "true":"false") << endl;
    coordSet.insert(duplicate);
    coordSet.insert(anotherone);

    list<Coord2D> list;
    for (Coord2D element : coordSet) {
        list.push_back(element);
    }
    cout << "Set: ";
    for (Coord2D element : coordSet) {
        cout << element << " ";
    }
    cout << endl;
    cout << "List: ";
    for (Coord2D element : list) {
        cout << element << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    cout << "Hello World!" << endl;
    if(argc > 2) {
        cout << "Too many arguments!" << endl;
        exit(1);
    }
    else if(argc == 1) {
        testGenerateGameGrid(INT_MAX);
    }
    else {
        int numOfGrids = atoi(argv[1]);
        auto startTime = std::chrono::steady_clock::now();
        testGenerateGameGrid(numOfGrids);
        auto endTime = std::chrono::steady_clock::now();
        cout << "Took " << std::chrono::duration<double,milli>(endTime-startTime).count() << "ms to generate grid(s)"<<endl;
    }
}
