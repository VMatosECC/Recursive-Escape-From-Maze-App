// Recursive-Escape-From-Maze-App.cpp 
// Goal: Recursively find a path from a given starting point
//       to an exit cell ('e'). The 'blind' exploratory process 
//       is implemented using the following order go north, south, 
//       east and finally west (if necessary.)
// --------------------------------------------------------------------


#include <iostream>
#include <vector>
using namespace std;

//-------------------------------------------------------
//maze: 'o' (free), 'b' (blocked), 'e' (exit), '*' (visited), 's' (starting point)
//char maze[4][5]{
vector<vector<char>> maze
{
    {'o', 'e', 'b', 'e', 'o', },
    {'o', 'b', 's', 'o', 'b', },
    {'o', 'o', 'o', 'b', 'b', },
    {'b', 'b', 'o', 'b', 'b', }
};

const int TROWS = maze.size();
const int TCOLS = maze[0].size();
//Prototypes ----------------------------------------
void showMaze(vector <vector<char>> maze);
bool escape(vector<vector<char>>& maze, int row, int col, vector<pair<int, int>>& path);

int main()
{

    showMaze(maze);

    vector<pair<int, int>> path;
    int startingRow = 1;
    int startingCol = 2;

    escape(maze, startingRow, startingCol, path);

    if (path.size() == 0)
    {
        cout << "\nNo escape path was found\n";
    }
    else
    {
        cout << "\n\tA escape path is: " << endl;
        for (auto cell : path) {
            cout << "\t( " << cell.first << ", " << cell.second << ")" << endl;
        }
    }
    cout << "\nAll done!\n";
}
//--------------------------------------------------
bool escape(vector<vector<char>>& maze, int row, int col, vector<pair<int, int>>& path)
{
    //Is the following cell promising?
    if (row >= TROWS || row < 0 ||
        col >= TCOLS || col < 0 ||
        maze[row][col] == '*' || maze[row][col] == 'b')
    {
        return false;    //Bad cell - return, try other options (if any!)
    }
    
    //put current cell into the exit path
    path.emplace_back(row, col);    

    //did we arrived to an exit?
    if (maze[row][col] == 'e') return true;

    //General recursion - Initiate exploration from current cell
    maze[row][col] = '*';                           //mark cell as visited

    if (escape(maze, row - 1, col, path) ||         //go north
        escape(maze, row + 1, col, path) ||         //go south
        escape(maze, row, col + 1, path) ||         //go east
        escape(maze, row, col - 1, path))           //go west
    {
        return true;                                //success - solution found
    }
    else
    {
        path.pop_back();                            //cell doesn't help
        return false;                               //no solution from here
                                                    //return, try pending options
    }

}



// -------------------------------------------------
void showMaze(vector <vector<char>> maze)
{
    cout << endl;
    for (int row = 0; row < TROWS; row++)
    {
        for (int col = 0; col < TCOLS; col++)
        {
            cout << "\t" << maze[row][col];
        }
        cout << endl;
    }
}