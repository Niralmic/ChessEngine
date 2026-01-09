#include "Chess.hpp"
#include "tests.hpp"
/*
TODO
1. превращение пешки не откатывается(как будет время) done
2. роккировка done
3. для пешки написать функцию IsFieldUnderControl и ее использовать при проверке шаха done
4. Check_Move переименовать в CheckMove done
5. Пат done
*/


using namespace std;
using FigureTypeId = char;

/*
h2 h4
OK
a7 a6
OK
h4 h5
OK
e7 e5
OK
h5 h6
OK
0-0-0
OK
h6 g7
OK
c8 b8
OK
g7 h8
In which figure do you want to promote your pawn?
rook
OK
e5 e4
OK
e2 e3
OK
d8 f8
OK
h8 f8
OK
b8 a7
OK
h1 h7
OK
a7 b6
OK
h7 h6
OK
b6 c6
------
h2 h4
e7 e5
h4 h5
e8 e7
h5 h6
g7 h6
h1 h6
e7 e6
--------
a2 a4
b7 b5
a4 b5
a7 a5
a1 a5
e8 f8
a5 a8
--------
a2 a4
b7 b5
a4 b5
a7 a5
b5 a6
a7 b8
a8 b8
b8 c6
a6 a7
h7 h5
a7 b8
knight
*/
int main()
{
    DoTests();
    Chess c;
    c.Init();
    FigureTypeId promote = '0'; // идентификатор превращения пешки
    string f, t;
    while(true)
    {
        unique_ptr<Figure> nptr = nullptr;
        cin >> f;
        if(f == "end") // если пользователь хочет завершить программу
            break;
        if(f == "new game") // новая игра
            c.NewGame();
        if(f == "0-0" || f == "0-0-0") // если пользователь хочет сделать роккировку
        {
            if(f == "0-0")
            {
                Cord from(10, 10);
                Cord to(10, 10);
                MMove m(from, to, move(nptr));
                if(!c.CMove(move(m), promote))
                    cout << "This move is not possible!" << endl;
                else
                {
                    cout << "OK" << endl;
                    if(promote == 'W' || promote == 'B' || promote == 'S')
                    {
                        string game_over = AfterGameEnds(promote);
                        if(game_over == "end") // если пользователь хочет завершить программу
                            break;
                        if(game_over == "new game")
                            c.NewGame();
                    }
                }
            }
            else
            {
                Cord from(11, 11);
                Cord to(11, 11);
                MMove m(from, to, move(nptr));
                if(!c.CMove(move(m), promote))
                    cout << "This move is not possible!" << endl;
                else
                {
                    cout << "OK" << endl;
                    if(promote == 'W' || promote == 'B' || promote == 'S')
                    {
                        string game_over = AfterGameEnds(promote);
                        if(game_over == "end") // если пользователь хочет завершить программу
                            break;
                        if(game_over == "new game")
                            c.NewGame();
                    }
                }
            }

        }
        else
        {
            cin >> t;
            Cord from = FieldToCord(f);
            Cord to = FieldToCord(t);
            MMove m(from, to, move(nptr));
            if(c.GetBoardField(from) != nullptr && c.GetBoardField(from)->GetType() == 'p') // обработка случая где пешка доходит до последней горизонтали
            {

                if((c.GetBoardField(from)->GetColor() == White && from.r == 1 && to.r == 0) || (c.GetBoardField(from)->GetColor() == Black && from.r == 6 && to.r == 7))
                {
                    cout << "In which figure do you want to promote your pawn?" << endl;
                    string tpawn;
                    while(promote == '0')
                    {
                        cin >> tpawn;
                        promote = StringToChar(tpawn);
                    }
                    if(!c.CMove(move(m), promote))
                        cout << "This move is not possible!" << endl;
                    else
                    {
                        cout << "OK" << endl;
                        if(promote == 'W' || promote == 'B' || promote == 'S')
                        {
                            string game_over = AfterGameEnds(promote);
                            if(game_over == "end") // если пользователь хочет завершить программу
                                break;
                            if(game_over == "new game")
                                c.NewGame();
                        }
                    }
                    promote = '0';
                }
                else
                {
                    if(!c.CMove(move(m), promote))
                        cout << "This move is not possible!" << endl;
                    else
                    {
                        cout << "OK" << endl;
                        if(promote == 'W' || promote == 'B' || promote == 'S')
                        {
                            string game_over = AfterGameEnds(promote);
                            if(game_over == "end") // если пользователь хочет завершить программу
                                break;
                            if(game_over == "new game")
                                c.NewGame();
                        }
                    }

                }

            }
            else
            {
                bool is_move_correct = c.CMove(move(m), promote);
                if(!is_move_correct)
                    cout << "This move is not possible!" << endl;
                else
                {
                    cout << "OK" << endl;
                    if(promote == 'W' || promote == 'B' || promote == 'S')
                    {
                        string game_over = AfterGameEnds(promote);
                        if(game_over == "end") // если пользователь хочет завершить программу
                            break;
                        if(game_over == "new game")
                            c.NewGame();
                    }
                }

            }
        }

    }
    return 0;
}
