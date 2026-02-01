#pragma once
#include<string>
#include <cstdint>


using namespace std;
using FigureTypeId = char;

enum Color
{
    White = 1,
    Black = 2
};

struct Cord
{
    int r; // строка
    int c; // столбец
    Cord(int row, int col) : r(row), c(col) {}
    Cord() : r(0), c(0) {}
};

enum StateWhite : uint8_t
{
    checkWhite      = 1 << 0,
    checkmateWhite  = 1 << 1,
    stalemateWhite  = 1 << 2,
    castlingMadeWhite   = 1 << 3,
};

enum StateBlack : uint8_t
{
    checkBlack      = 1 << 0,
    checkmateBlack  = 1 << 1,
    stalemateBlack  = 1 << 2,
    castlingMadeBlack = 1 << 3,
};

inline Cord FieldToCord(const string &pos) // превращает координату шахматного поля в числовую координату типа Cord
{
    Cord crd;
    crd.c = pos[0] - 'a';
    crd.r = 8 - (pos[1] - '0');
    return crd;
}

FigureTypeId StringToChar(string fig)
{
    if (fig == "knight") return 'k';
    else if (fig == "queen") return 'q';
    else if (fig == "rook") return 'r';
    else if (fig == "bishop") return 'b';
    else return '0';
}

/*string AfterGameEnds(FigureTypeId& promote)
{
    if(promote == 'W')
    {
        promote = '0';
        cout << "White won! Enter \"new game\" to start a new game! Enter \"end\" to exit" << endl;
        string new_game;
        int cnt = 0;
        while(true)
        {
            getline(cin, new_game);
            if(new_game == "end") // если пользователь хочет завершить программу
                return new_game;
            if(new_game == "new game")
            {
                cout << "OK" << endl;
                return new_game;
            }
            else
            {
                if(cnt != 0)
                    cout << "False input! Enter \"new game\" to start a new game enter \"end\" to exit" << endl;
            }
            cnt++;
        }
    }
    if(promote == 'B')
    {
        promote = '0';
        cout << "Black won! Enter \"new game\" to start a new game enter \"end\" to exit" << endl;
        string new_game;
        int cnt = 0;
        while(true)
        {
            getline(cin, new_game);
            if(new_game == "end") // если пользователь хочет завершить программу
                return new_game;
            if(new_game == "new game")
            {
                cout << "OK" << endl;
                return new_game;
            }
            else
            {
                if(cnt != 0)
                    cout << "False input! Enter \"new game\" to start a new game enter \"end\" to exit" << endl;
            }
            cnt++;
        }
    }
    if(promote == 'S')
    {
        promote = '0';
        cout << "Stalemate! Draw! Enter \"new game\" to start a new game enter \"end\" to exit" << endl;
        string new_game;
        int cnt = 0;
        while(true)
        {
            getline(cin, new_game);
            if(new_game == "end") // если пользователь хочет завершить программу
                return new_game;
            if(new_game == "new game")
            {
                cout << "OK" << endl;
                return new_game;
            }
            else
            {
                if(cnt != 0)
                    cout << "False input! Enter \"new game\" to start a new game enter \"end\" to exit" << endl;
            }
            cnt++;
        }
    }
}*/

