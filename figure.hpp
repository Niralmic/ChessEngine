#pragma once
#include "structures.hpp"

class Board;
class MMove;

using FigureTypeId = char;

class Figure // базовый класс фигура
{
    private:
        Cord _field;
        Color _color;
        unsigned int moved = 0;

    public:
        Figure(Cord field, Color color) : _color(color), _field(field) {}
        Color GetColor()const
        {
            return _color;
        }
        Cord GetField()const
        {
            return _field;
        }
        unsigned int GetMoved() const // ходила ли фигура
        {
            return moved;
        }
        void ChangeField(Cord new_field)
        {
            _field = new_field;
        }
        void PlusMoved() // если фигура походила надо вызвать эту функцию
        {
            moved++;
        }

        void MinusMoved() // если фигура походила надо вызвать эту функцию
        {
            moved--;
        }

        virtual FigureTypeId GetType()const = 0;

        virtual vector<Cord> AllPossibleMoves(const Board* b)const = 0;
        virtual bool CheckMove(const MMove& m, const Board* b)const = 0; // Базовые проверки корректности хода(без учета ситуации на доске)
        virtual bool CouldTake(const MMove& m, const Board* b) const // могла бы фигура походить так(у всех кроме пешки логика совпадает с CheckMove)
        {
            if(CheckMove(m, b))
                return true;
            return false;
        }
        virtual ~Figure() = default;

        //virtual vector<MMove> AllPossibleMoves(const Board* b)const = 0;

};
