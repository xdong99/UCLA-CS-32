#ifndef MESA_INCLUDED
#define MESA_INCLUDED

#include "globals.h"
#include "History.h"


class Player;
class Gark;

class Mesa
{
public:
    // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    History& history();

    // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    History m_history;
    int     m_nGarks;
};

#endif // MESA_INCLUDED
