#pragma once
#include <vector>
#include<iostream>
#include <memory>
#include "structures.hpp"
#include "figure.hpp"
#include "move.hpp"

using namespace std;

class Pawn;

class Board
{
    private:
        /* board[8][8] =
        {
              {-1, -1, -1, -1, -1, -1, -1, -1},//0
              {-1, -1, -1, -1, -1, -1, -1, -1},//1
              {-1, -1, -1, -1, -1, -1, -1, -1},//2
              {-1, -1, -1, -1, -1, -1, -1, -1},//3
              {-1, -1, -1, -1, -1, -1, -1, -1},//4
              {-1, -1, -1, -1, -1, -1, -1, -1},//5
              {-1, -1, -1, -1, -1, -1, -1, -1},//6
              {-1, -1, -1, -1, -1, -1, -1, -1},//7
                0   1   2   3   4   5   6   7
        };*/
        unique_ptr<Figure> board[8][8] = { nullptr };
        vector<MMove> moves; // вектор ходов

    public:
        Board()
        {

        }

        Cord GetLastMoveCords(Cord& to) const // координаты последнего хода(для взятия на проходе)
        {
            to = moves.back().GetTo();
            return moves.back().GetFrom();
        }

        const unique_ptr<Figure>& GetField(Cord c) const // вернуть поле на доске
        {
            return board[c.r][c.c];
        }
        void MakeCastling(MMove&& m) // делает все роккировки
        {
            if(m.GetFrom().r == 10 && m.GetFrom().c == 10 && m.GetTo().r == 10 && m.GetTo().c == 10) // Short Castling White
            {
                board[7][4]->PlusMoved();
                board[7][7]->PlusMoved();
                board[7][6] = move(board[7][4]);
                board[7][5] = move(board[7][7]);
                board[7][6]->ChangeField(Cord(7, 6));
                board[7][5]->ChangeField(Cord(7, 5));
                m.CastlingMove();
                moves.push_back(move(m));
                return;
            }
            if(m.GetFrom().r == 10 && m.GetFrom().c == 10 && m.GetTo().r == 11 && m.GetTo().c == 11) // Short Castling Black
            {
                board[0][4]->PlusMoved();
                board[0][7]->PlusMoved();
                board[0][6] = move(board[0][4]);
                board[0][5] = move(board[0][7]);
                board[0][6]->ChangeField(Cord(0, 6));
                board[0][5]->ChangeField(Cord(0, 5));
                m.CastlingMove();
                moves.push_back(move(m));
                return;
            }
            if(m.GetFrom().r == 11 && m.GetFrom().c == 11 && m.GetTo().r == 11 && m.GetTo().c == 11) // Long Castling White
            {
                board[7][4]->PlusMoved();
                board[7][0]->PlusMoved();
                board[7][2] = move(board[7][4]);
                board[7][3] = move(board[7][0]);
                board[7][2]->ChangeField(Cord(7, 2));
                board[7][3]->ChangeField(Cord(7, 3));
                m.CastlingMove();
                moves.push_back(move(m));
                return;
            }
            if(m.GetFrom().r == 11 && m.GetFrom().c == 11 && m.GetTo().r == 12 && m.GetTo().c == 12) // Long Castling Black
            {
                board[0][4]->PlusMoved();
                board[0][0]->PlusMoved();
                board[0][2] = move(board[0][4]);
                board[0][3] = move(board[0][0]);
                board[0][2]->ChangeField(Cord(0, 2));
                board[0][3]->ChangeField(Cord(0, 3));
                m.CastlingMove();
                moves.push_back(move(m));
                return;
            }
        }
        void Move(MMove&& m, unique_ptr<Figure> promote) // сделать ход
        {
            if(m.GetFrom().r == 10 || m.GetFrom().r == 11)
            {
                MakeCastling(move(m));
                return;
            }

            if(promote != nullptr)
            {
                m.ChangeKilled(move(board[m.GetTo().r][m.GetTo().c]));
                m.ChangePromotedPawn(move(board[m.GetFrom().r][m.GetFrom().c]));
                board[m.GetTo().r][m.GetTo().c] = move(promote);
                board[m.GetTo().r][m.GetTo().c]->ChangeField(m.GetTo());
                board[m.GetFrom().r][m.GetFrom().c] = nullptr;
                m.PromotionMove();
                moves.push_back(move(m));
                return;
            }

            if(GetField(m.GetFrom())->GetType() == 'p' && GetField(m.GetTo()) == nullptr && max(m.GetFrom().c, m.GetTo().c) - min(m.GetFrom().c, m.GetTo().c) == 1) // взяте на проходе
            {
                board[m.GetFrom().r][m.GetFrom().c]->PlusMoved();
                if(board[m.GetFrom().r][m.GetFrom().c]->GetColor() == White)
                    m.ChangeKilled(move(board[m.GetTo().r + 1][m.GetTo().c]));
                else
                    m.ChangeKilled(move(board[m.GetTo().r - 1][m.GetTo().c]));
                board[m.GetTo().r][m.GetTo().c] = move(board[m.GetFrom().r][m.GetFrom().c]);
                board[m.GetTo().r][m.GetTo().c]->ChangeField(Cord(m.GetTo().r, m.GetTo().c));
                m.EnpassantMove();
                moves.push_back(move(m));
            }
            else // обычный ход
            {
                board[m.GetFrom().r][m.GetFrom().c]->PlusMoved();
                m.ChangeKilled(move(board[m.GetTo().r][m.GetTo().c]));
                board[m.GetTo().r][m.GetTo().c] = move(board[m.GetFrom().r][m.GetFrom().c]);
                board[m.GetTo().r][m.GetTo().c]->ChangeField(Cord(m.GetTo().r, m.GetTo().c));
                moves.push_back(move(m));
            }

        }

        void SetFigure(unique_ptr<Figure> upf, Cord cord) // поставить фигуру
        {
            board[cord.r][cord.c] = move(upf);
        }

        void Clear() // очистка
        {
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                    board[i][j] = nullptr;
            moves.clear();
        }

        void UnMakeCastling()
        {
            if(moves.back().GetFrom().r == 10 && moves.back().GetFrom().c == 10 && moves.back().GetTo().r == 10 && moves.back().GetTo().c == 10) // Short Castling White
            {
                board[7][4] = move(board[7][6]);
                board[7][7] = move(board[7][5]);
                board[7][4]->ChangeField(Cord(7, 4));
                board[7][7]->ChangeField(Cord(7, 7));
                board[7][4]->MinusMoved();
                board[7][7]->MinusMoved();
                moves.pop_back();
                return;
            }
            if(moves.back().GetFrom().r == 10 && moves.back().GetFrom().c == 10 && moves.back().GetTo().r == 11 && moves.back().GetTo().c == 11) // Short Castling Black
            {
                board[0][4] = move(board[0][6]);
                board[0][7] = move(board[0][5]);
                board[0][4]->ChangeField(Cord(0, 4));
                board[0][7]->ChangeField(Cord(0, 7));
                board[0][4]->MinusMoved();
                board[0][7]->MinusMoved();
                moves.pop_back();
                return;
            }
            if(moves.back().GetFrom().r == 11 && moves.back().GetFrom().c == 11 && moves.back().GetTo().r == 11 && moves.back().GetTo().c == 11) // Long Castling White
            {
                board[7][4] = move(board[7][2]);
                board[7][0] = move(board[7][3]);
                board[7][4]->ChangeField(Cord(7, 4));
                board[7][0]->ChangeField(Cord(7, 0));
                board[7][4]->MinusMoved();
                board[7][0]->MinusMoved();
                moves.pop_back();
                return;
            }
            if(moves.back().GetFrom().r == 11 && moves.back().GetFrom().c == 11 && moves.back().GetTo().r == 12 && moves.back().GetTo().c == 12) // Long Castling Black
            {
                board[0][4] = move(board[0][2]);
                board[0][0] = move(board[0][3]);
                board[0][4]->ChangeField(Cord(0, 4));
                board[0][0]->ChangeField(Cord(0, 0));
                board[0][4]->MinusMoved();
                board[0][0]->MinusMoved();
                moves.pop_back();
                return;
            }
            return;
        }

        void BackMove() // сделать ход назад
        {
            if (moves.empty())
                return;
            if(moves.back().GetFrom().r == 10 || moves.back().GetFrom().r == 11)
            {
                UnMakeCastling();
                return;
            }

            if(moves.back().GetPromotion() == true)
            {
                board[moves.back().GetFrom().r][moves.back().GetFrom().c] = move(moves.back().GetKilledPawn());
                board[moves.back().GetFrom().r][moves.back().GetFrom().c]->ChangeField(moves.back().GetFrom());
                board[moves.back().GetTo().r][moves.back().GetTo().c] = move(moves.back().GetKilled());
                if(board[moves.back().GetTo().r][moves.back().GetTo().c] != nullptr)
                    board[moves.back().GetTo().r][moves.back().GetTo().c]->ChangeField(moves.back().GetTo());
                moves.pop_back();
                return;
            }

            if(moves.back().GetEnpassant() == true) // отменить взятие на проходе
            {
                if(board[moves.back().GetTo().r][moves.back().GetTo().c]->GetColor() == White)
                {
                    board[moves.back().GetTo().r + 1][moves.back().GetTo().c] = move(moves.back().GetKilled());
                    board[moves.back().GetTo().r + 1][moves.back().GetTo().c]->ChangeField(Cord(moves.back().GetTo().r + 1, moves.back().GetTo().c));
                }
                else
                {
                    board[moves.back().GetTo().r - 1][moves.back().GetTo().c] = move(moves.back().GetKilled());
                    board[moves.back().GetTo().r - 1][moves.back().GetTo().c]->ChangeField(Cord(moves.back().GetTo().r - 1, moves.back().GetTo().c));
                }


                board[moves.back().GetFrom().r][moves.back().GetFrom().c] = move(board[moves.back().GetTo().r][moves.back().GetTo().c]);
                board[moves.back().GetFrom().r][moves.back().GetFrom().c]->ChangeField(Cord(moves.back().GetFrom().r, moves.back().GetFrom().c));
                board[moves.back().GetFrom().r][moves.back().GetFrom().c]->MinusMoved();

                moves.pop_back();
            }
            else // обычный ход
            {
                board[moves.back().GetFrom().r][moves.back().GetFrom().c] = move(board[moves.back().GetTo().r][moves.back().GetTo().c]);
                board[moves.back().GetFrom().r][moves.back().GetFrom().c]->ChangeField(Cord(moves.back().GetFrom().r, moves.back().GetFrom().c));
                board[moves.back().GetFrom().r][moves.back().GetFrom().c]->MinusMoved();
                board[moves.back().GetTo().r][moves.back().GetTo().c] = move(moves.back().GetKilled());
                if(board[moves.back().GetTo().r][moves.back().GetTo().c] != nullptr)
                    board[moves.back().GetTo().r][moves.back().GetTo().c]->ChangeField(Cord(moves.back().GetTo().r, moves.back().GetTo().c));
                moves.pop_back();
            }

        }

};
