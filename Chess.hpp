#pragma once
#include "board.hpp"
#include "figure.hpp"
#include "pawn.hpp"
#include "king.hpp"
#include "move.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "state.hpp"
#include <cstdint>
#include <vector>
#include <utility>
using FigureTypeId = char;
class Chess // класс игры в шахматы
{
    private:
        Board brd; // доска
        Color _zug = White; // очередь хода
        State _state;

        unique_ptr<Figure> MakeFigure(FigureTypeId figureId, Cord cord, Color color) // фабрика фигур
        {
             unique_ptr<Figure> nptr = nullptr;
             switch(figureId)
             {
                 case 'p': return make_unique<Pawn>(cord, color);
                 case 'K': return make_unique<King>(cord, color);
                 case 'r': return make_unique<Rook>(cord, color);
                 case 'k': return make_unique<Knight>(cord, color);
                 case 'b': return make_unique<Bishop>(cord, color);
                 case 'q': return make_unique<Queen>(cord, color);
                 default: return nptr;
            }
        }
        void ReverseZug()
        {
            if(_zug == White)
            {
                _zug = Black;
                return;
            }
            _zug = White;
        }
        Cord SearchKing(Color col)
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    Cord a(i, j);
                    const auto &fig = brd.GetField(a);
                    if(fig != nullptr && fig->GetType() == 'K' && fig->GetColor() == col)
                        return a;
                }
            }
            Cord not_found(-1, -1);
            return not_found;
        }
        bool IsCheck(Cord pos, Color col) // функция проверяет есть ли шах королю
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Cord a(i, j);
                    const auto &fig = brd.GetField(a);
                    if(fig != nullptr && fig->GetColor() != col) // ищем фигуры другого цвета
                    {
                        unique_ptr<Figure> nptr = nullptr;
                        MMove mv(a, pos, std::move(nptr));
                        if(fig->CouldTake(mv, &brd))
                            return true;
                    }
                }
            }
            return false;
        }

    public:

        bool IsMate(Color z, FigureTypeId promote) // есть ли мат
        {
            if(IsCheck(SearchKing(z), z))
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        Cord a(i, j);
                        const unique_ptr<Figure>& fig = brd.GetField(a);
                        if(fig != nullptr && fig->GetColor() == z) // ищем фигуры тогоже цвета
                        {
                            vector<Cord> possible_moves = fig->AllPossibleMoves(&brd);
                            for(int i = 0; i < possible_moves.size(); i++)
                            {
                                if(possible_moves[i].r != 10 && possible_moves[i].r != 11)
                                {
                                    unique_ptr<Figure> nptr = nullptr;
                                    MMove moove(a, possible_moves[i], move(nptr));
                                    brd.Move(move(moove), move(MakeFigure(promote, possible_moves[i], z)));
                                    if(!IsCheck(SearchKing(z), z))
                                    {
                                        brd.BackMove();
                                        return false;
                                    }
                                    brd.BackMove();
                                }
                            }
                        }
                    }
                }
                return true;
            }
            return false;
        }

        bool IsStaleMate(Color z, FigureTypeId promote) // есть ли пат
        {
            if(IsCheck(SearchKing(z), z))
                return false;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Cord a(i, j);
                    const unique_ptr<Figure>& fig = brd.GetField(a);
                    if(fig != nullptr && fig->GetColor() == z) // ищем фигуры тогоже цвета
                    {
                        vector<Cord> possible_moves = fig->AllPossibleMoves(&brd);
                        for(int i = 0; i < possible_moves.size(); i++)
                        {
                            unique_ptr<Figure> nptr = nullptr;
                            MMove moove(a, possible_moves[i], move(nptr));
                            brd.Move(move(moove), move(MakeFigure(promote, possible_moves[i], z)));
                            if(!IsCheck(SearchKing(z), z))
                            {
                                brd.BackMove();
                                return false;
                            }
                            brd.BackMove();
                        }
                    }
                }
            }
            return true;
        }

        bool CMove(MMove&& m, FigureTypeId& promote) // функция хода
        {
            if(IsMate(Black, promote)) // если мат черным
            {
                promote = 'W';
                _state.CheckmateBlack();
                return false;
            }
            if(IsMate(White, promote)) // если мат белым
            {
                promote = 'B';
                _state.CheckmateWhite();
                return false;
            }
            if(_zug == White)
            {
                if(IsStaleMate(White, promote)) // если пат белым
                {
                    promote = 'S';
                    _state.StalemateWhite();
                    return false;
                }
            }
            else
            {
                if(IsStaleMate(Black, promote)) // если пат черным
                {
                    promote = 'S';
                    _state.StalemateBlack();
                    return false;
                }
            }

            unique_ptr<Figure> nptr = nullptr;

            if(m.GetFrom().c == 10 && m.GetFrom().r == 10 && m.GetTo().c == 10 && m.GetTo().r == 10) // короткая роккировка
            {
                if(_zug == White)
                {
                    Cord whkingpos(7, 4);
                    if(brd.GetField(whkingpos) == nullptr || brd.GetField(whkingpos)->GetType() != 'K' || brd.GetField(whkingpos)->GetColor() != White) // король стоит там где должен
                        return false;
                    const auto &f = brd.GetField(whkingpos);
                    if(f->CheckMove(m, &brd))
                    {
                        for(int i = 4; i < 7; i++) // нет ли шаха королю и не проходит ли он через битое поле
                            if(IsCheck(Cord(7, i), _zug))
                                return false;
                        brd.Move(move(m), move(nptr)); // Short Castling White
                        if(IsMate(Black, promote))
                        {
                            promote = 'W';
                            _state.CheckmateBlack();
                            return true;
                        }
                        if(IsStaleMate(Black, promote))
                        {
                            promote = 'S';
                            _state.StalemateBlack();
                            return true;
                        }
                        ReverseZug(); // передача хода
                        return true;
                    }
                    return false;
                }
                Cord blkingpos(0, 4);
                if(brd.GetField(blkingpos) == nullptr || brd.GetField(blkingpos)->GetType() != 'K' || brd.GetField(blkingpos)->GetColor() != Black) // король стоит там где должен
                    return false;
                const auto &f = brd.GetField(blkingpos);
                if(f->CheckMove(m, &brd))
                {
                    for(int i = 4; i < 7; i++) // нет ли шаха королю и не проходит ли он через битое поле
                        if(IsCheck(Cord(0, i), _zug))
                            return false;
                    MMove scb(Cord(10, 10), Cord(11, 11), move(m.GetKilled())); // Short Castling Black
                    brd.Move(move(scb), move(nptr));
                    if(IsMate(White, promote))
                    {
                        promote = 'B';
                        _state.CheckmateWhite();
                        return true;
                    }
                    if(IsStaleMate(White, promote))
                    {
                        promote = 'S';
                        _state.StalemateWhite();
                        return true;
                    }
                    ReverseZug(); // передача хода
                    return true;
                }
                return false;
            }

            if(m.GetFrom().c == 11 && m.GetFrom().r == 11 && m.GetTo().c == 11 && m.GetTo().r == 11) // длинная роккировка
            {
                if(_zug == White)
                {
                    Cord whkingpos(7, 4);
                    if(brd.GetField(whkingpos) == nullptr || brd.GetField(whkingpos)->GetType() != 'K' || brd.GetField(whkingpos)->GetColor() != White) // король стоит там где должен
                        return false;
                    const auto &f = brd.GetField(whkingpos);
                    if(f->CheckMove(m, &brd))
                    {
                        for(int i = 4; i > 1; i--) // нет ли шаха королю и не проходит ли он через битое поле
                            if(IsCheck(Cord(7, i), _zug))
                                return false;
                        brd.Move(move(m), move(nptr)); // Long Castling White
                        if(IsMate(Black, promote))
                        {
                            promote = 'W';
                            _state.CheckmateBlack();
                            return true;
                        }
                        if(IsStaleMate(Black, promote))
                        {
                            promote = 'S';
                            _state.StalemateBlack();
                            return true;
                        }
                        ReverseZug(); // передача хода
                        return true;
                    }
                    return false;
                }
                Cord blkingpos(0, 4);
                if(brd.GetField(blkingpos) == nullptr || brd.GetField(blkingpos)->GetType() != 'K' || brd.GetField(blkingpos)->GetColor() != Black) // король стоит там где должен
                    return false;
                const auto &f = brd.GetField(blkingpos);
                if(f->CheckMove(m, &brd))
                {
                    for(int i = 4; i > 1; i--) // нет ли шаха королю и не проходит ли он через битое поле
                        if(IsCheck(Cord(0, i), _zug))
                            return false;
                    MMove lcb(Cord(11, 11), Cord(12, 12), move(m.GetKilled())); // Long Castling Black
                    brd.Move(move(lcb), move(nptr));
                    if(IsMate(White, promote))
                    {
                        promote = 'B';
                        _state.CheckmateWhite();
                        return true;
                    }
                    if(IsStaleMate(White, promote))
                    {
                        promote = 'S';
                        _state.StalemateWhite();
                        return true;
                    }
                    ReverseZug(); // передача хода
                    return true;
                }
                return false;
            }

            if (m.GetFrom().r < 0 || m.GetFrom().c < 0 || m.GetFrom().r > 7 || m.GetFrom().c > 7 || m.GetTo().r < 0 || m.GetTo().c < 0 || m.GetTo().r > 7 || m.GetTo().c > 7) // не выходим за рамки доски
                return false;

            if (brd.GetField(m.GetFrom()) == nullptr)// если некорректно задали координаты поля откуда
                return false;

            const auto &f = brd.GetField(m.GetFrom());
            const auto &f2 = brd.GetField(m.GetTo());

            if (f->GetColor() != _zug) // контроль очередности хода
                return false;

            if(f2 != nullptr && f->GetColor() == f2->GetColor()) // если фигура хочет походить, на поле где стоит фигура того же цвета то ход сделать нельзя
                return false;

            if (f->CheckMove(m, &brd))
            {
                brd.Move(move(m), move(MakeFigure(promote, m.GetTo(), _zug)));
                Cord king = SearchKing(_zug);
                if(!IsCheck(king, _zug))
                {
                    if(_zug == White)
                    {
                        if(IsMate(Black, promote)) // если мат черным
                        {
                            promote = 'W';
                            _state.CheckmateBlack();
                            return true;
                        }
                        if(IsStaleMate(Black, promote)) // если пат черным
                        {
                            promote = 'S';
                            _state.StalemateBlack();
                            return true;
                        }
                        ReverseZug(); // передача хода
                        return true;
                    }
                    if(IsMate(White, promote)) // если мат белым
                    {
                        promote = 'B';
                        _state.CheckmateWhite();
                        return true;
                    }
                    if(IsStaleMate(White, promote)) // если пат белым
                    {
                        promote = 'S';
                        _state.StalemateWhite();
                        return true;
                    }
                    ReverseZug(); // передача хода
                    return true;
                }
                brd.BackMove();
            }
            return false;
        }

        void SetFigureOnBoard(FigureTypeId figure, Cord place, Color color) // поставить фигуру на доску
        {
            brd.SetFigure(MakeFigure(figure, place, color), place);
        }

        void SetZug(Color zug) // задать чей ход
        {
            _zug = zug;
        }

        void Init() // расстановка начальной позиции
        {
            for (int i = 0; i < 8; i++) // ставим пешки
            {
                brd.SetFigure(MakeFigure('p', Cord(6, i), White), Cord(6, i));
                brd.SetFigure(MakeFigure('p', Cord(1, i), Black), Cord(1, i));
            }

            // ставим королей
            brd.SetFigure(MakeFigure('K', Cord(7, 4), White), Cord(7, 4));
            brd.SetFigure(MakeFigure('K', Cord(0, 4), Black), Cord(0, 4));

            // ставим ладьи
            brd.SetFigure(MakeFigure('r', Cord(7, 7), White), Cord(7, 7));
            brd.SetFigure(MakeFigure('r', Cord(7, 0), White), Cord(7, 0));
            brd.SetFigure(MakeFigure('r', Cord(0, 7), Black), Cord(0, 7));
            brd.SetFigure(MakeFigure('r', Cord(0, 0), Black), Cord(0, 0));

            // ставим коней
            brd.SetFigure(MakeFigure('k', Cord(7, 6), White), Cord(7, 6));
            brd.SetFigure(MakeFigure('k', Cord(7, 1), White), Cord(7, 1));
            brd.SetFigure(MakeFigure('k', Cord(0, 6), Black), Cord(0, 6));
            brd.SetFigure(MakeFigure('k', Cord(0, 1), Black), Cord(0, 1));

            // ставим слонов
            brd.SetFigure(MakeFigure('b', Cord(7, 5), White), Cord(7, 5));
            brd.SetFigure(MakeFigure('b', Cord(7, 2), White), Cord(7, 2));
            brd.SetFigure(MakeFigure('b', Cord(0, 5), Black), Cord(0, 5));
            brd.SetFigure(MakeFigure('b', Cord(0, 2), Black), Cord(0, 2));

            //ставим ферзей
            brd.SetFigure(MakeFigure('q', Cord(7, 3), White), Cord(7, 3));
            brd.SetFigure(MakeFigure('q', Cord(0, 3), Black), Cord(0, 3));
        }

        Figure* GetBoardField(Cord crd)
        {
            return brd.GetField(crd).get();
        }

        State GetState() {return _state;}

        void Clear() // очистить доску и задать ход белых
        {
            brd.Clear();
            _zug = White;
        }

        void NewGame() // очистка и расстановка начальной позиции
        {
            Clear();
            Init();
        }
};
