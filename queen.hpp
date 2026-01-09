#pragma once
#include"structures.hpp"
#include"figure.hpp"
#include "rook.hpp"
#include "bishop.hpp"

class Queen : public Figure // פונחü
{
    public:
        Queen(Cord field, Color color) : Figure(field, color) {}//, _bishop(field, color), _rook(field, color)
        virtual FigureTypeId GetType() const override
        {
            return 'q';
        }
        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            Bishop bishop(GetField(), GetColor());
            Rook   rook(GetField(), GetColor());

            vector<Cord> possibleMovesBishop = bishop.AllPossibleMoves(b);
            vector<Cord> possibleMovesRook   = rook.AllPossibleMoves(b);
            vector<Cord> possibleMovesQueen;

            for(int i = 0; i < possibleMovesBishop.size(); i++)
                possibleMovesQueen.emplace_back(possibleMovesBishop[i]);

            for(int i = 0; i < possibleMovesRook.size(); i++)
                possibleMovesQueen.emplace_back(possibleMovesRook[i]);

            return possibleMovesQueen;
        }
        bool CheckMove(const MMove& m, const Board* b) const override
        {
            vector<Cord> v = AllPossibleMoves(b);
            bool right_cord = false;
            for (int i = 0; i < v.size(); i++)
                if (m.GetTo().r == v[i].r && m.GetTo().c == v[i].c) { right_cord = true; break; }
            return right_cord;
        }

};
