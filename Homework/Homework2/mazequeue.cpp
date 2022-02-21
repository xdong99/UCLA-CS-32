#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X.X..X...X",
//        "X....XXX.X",
//        "X.XXXX.X.X",
//        "X......XXX",
//        "X.XX.X...X",
//        "X.X..X.X.X",
//        "X.X.XXXX.X",
//        "X.X...X..X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}

//int main()
//{
//    stack<Coord> coordStack;  // declare a stack of Coords
//
//    Coord a(5, 6);
//    coordStack.push(a);          // push the coordinate (5,6)
//    coordStack.push(Coord(3, 4)); // push the coordinate (3,4)
//
//    Coord b = coordStack.top();  // look at top item in the stack
//    coordStack.pop();            // remove the top item from stack
//    if (coordStack.empty())      // Is the stack empty?
//        cout << "empty!" << endl;
//    cout << coordStack.size() << endl; // num of elements
//}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '-';

    while (coordQueue.empty() == false)
    {
        Coord a = coordQueue.front();
        //cout << "(" << a.r() << ", " << a.c() << ")" << endl;
        coordQueue.pop();
        if (a.r() == er && a.c() == ec)
        {
            return true;
        }
        else
        {
            //Check if moving WEST is available, push if yes
            if (maze[a.r()][a.c() - 1] == '.')
            {
                coordQueue.push(Coord(a.r(), a.c() - 1));
                maze[a.r()][a.c() - 1] = '-';
            }
            //Check if moving South is available, push if yes
            if (maze[a.r() + 1][a.c()] == '.')
            {
                coordQueue.push(Coord(a.r() + 1, a.c()));
                maze[a.r() + 1][a.c()] = '-';
            }
            //Check if moving EAST is available, push if yes
            if (maze[a.r()][a.c() + 1] == '.')
            {
                coordQueue.push(Coord(a.r(), a.c() + 1));
                maze[a.r()][a.c() + 1] = '-';
            }
            //Check if moving North is available, push if yes
            if (maze[a.r() - 1][a.c()] == '.')
            {
                coordQueue.push(Coord(a.r() - 1, a.c()));
                maze[a.r() - 1][a.c()] = '-';
            }
        }
    }
    return false;
}