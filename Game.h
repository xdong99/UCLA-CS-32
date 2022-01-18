#ifndef GAME_INCLUDED 
#define GAME_INCLUDED

class Mesa;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

private:
    Mesa* m_mesa;
};

#endif // GAME_INCLUDED 

