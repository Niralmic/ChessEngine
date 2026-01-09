#pragma once
#include <iostream>
#include <memory>
#include "figure.hpp"
#include "structures.hpp"

/*
MMove - контейнер, который хранит полную информацию о ходе, включая убитую фигуру, фигуру превращения,
тип хода(рокировка, взятие на проходе, превращение)
*/

class MMove
{
    private:
        Cord _from;
        Cord _to;
        unique_ptr<Figure> _killed = nullptr;
        unique_ptr<Figure> _promoted_pawn = nullptr;
        bool _enpassant = false; // взятие на проходе
        bool _castling = false; // роккировка
        bool _transformation = false; // превращение пешки

    public:
        MMove(Cord from, Cord to, unique_ptr<Figure> killed) : _from(from), _to(to)  {_killed = move(killed);}
        MMove() : _from(0, 0), _to(0, 0) {}

        MMove(const MMove&) = delete;
        MMove& operator=(const MMove&) = delete;
        MMove(MMove&&) = default;
        MMove& operator=(MMove&&) = default;

        // менять спец. параметры хода
        void EnpassantMove() {_enpassant = true;}
        void CastlingMove() {_castling = true;}
        void PromotionMove() {_transformation = true;}
        void ChangeKilled(unique_ptr<Figure> killed) {_killed = move(killed);}
        void ChangePromotedPawn(unique_ptr<Figure> promoted_pawn) {_promoted_pawn = move(promoted_pawn);}

        // получить координаты хода
        Cord GetFrom() const {return _from;}
        Cord GetTo() const {return _to;}

        // получить информацию об убитой фигуре
        Figure* LookAtKilled() const {return _killed.get();}
        unique_ptr<Figure> GetKilled() {return move(_killed);}
        unique_ptr<Figure> GetKilledPawn() {return move(_promoted_pawn);}

        // получить спец. параметры хода
        bool GetEnpassant() {return _enpassant; }
        bool GetCastling() {return _castling; }
        bool GetPromotion() {return _transformation; }

};
