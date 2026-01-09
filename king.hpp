#pragma once
#include"structures.hpp"
#include"figure.hpp"

using FigureTypeId = char;

class King : public Figure // король
{
    public:
        King(Cord field, Color color) : Figure(field, color) {}
        virtual FigureTypeId GetType() const override
        {
            return 'K';
        }

        bool ShortCastlingPossible(const Board* b) const
        {
            if(GetMoved() != 0) // если король ходил, то рокировка невозможна
                return false;
            if(GetColor() == White)
            {
                Cord whrookpos(7, 7);
                if(b->GetField(whrookpos) == nullptr || b->GetField(whrookpos)->GetType() != 'r' || b->GetField(whrookpos)->GetColor() != White) // действительно ли на поле стоит белая ладья
                        return false;
                if(b->GetField(whrookpos)->GetMoved() != 0) // если ладья ходила, то рокировка невозможна
                    return false;
                for(int i = 5; i <= 6; i++) // нет ли фигур между королем и ладьей
                    if(b->GetField(Cord(7, i)) != nullptr)
                        return false;
                return true;
            }
            Cord blrookpos(0, 7);
            if(b->GetField(blrookpos) == nullptr || b->GetField(blrookpos)->GetType() != 'r' || b->GetField(blrookpos)->GetColor() != Black) // действительно ли на поле стоит белая ладья
                    return false;
            if(b->GetField(blrookpos)->GetMoved() != 0) // если ладья ходила, то рокировка невозможна
                return false;
            for(int i = 5; i <= 6; i++) // нет ли фигур между королем и ладьей
                if(b->GetField(Cord(0, i)) != nullptr)
                    return false;
            return true;

        }

        bool LongCastlingPossible(const Board* b) const
        {
            if(GetMoved() != 0) // если король ходил, то рокировка невозможна
                return false;
            if(GetColor() == White)
            {
                Cord whrookpos(7, 0);
                if(b->GetField(whrookpos) == nullptr || b->GetField(whrookpos)->GetType() != 'r' || b->GetField(whrookpos)->GetColor() != White) // действительно ли на поле стоит белая ладья
                        return false;
                if(b->GetField(whrookpos)->GetMoved() != 0) // если ладья ходила, то рокировка невозможна
                    return false;
                for(int i = 3; i >= 1; i--) // нет ли фигур между королем и ладьей
                    if(b->GetField(Cord(7, i)) != nullptr)
                        return false;
                return true;
            }
            Cord blrookpos(0, 0);
            if(b->GetField(blrookpos) == nullptr || b->GetField(blrookpos)->GetType() != 'r' || b->GetField(blrookpos)->GetColor() != Black) // действительно ли на поле стоит белая ладья
                    return false;
            if(b->GetField(blrookpos)->GetMoved() != 0) // если ладья ходила, то рокировка невозможна
                return false;
            for(int i = 3; i >= 1; i--) // нет ли фигур между королем и ладьей
                if(b->GetField(Cord(0, i)) != nullptr)
                    return false;
            return true;
        }

        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            std::vector<Cord> v;
            v.emplace_back(GetField().r, GetField().c - 1);
            v.emplace_back(GetField().r, GetField().c + 1);
            v.emplace_back(GetField().r - 1, GetField().c);
            v.emplace_back(GetField().r + 1, GetField().c);
            v.emplace_back(GetField().r - 1, GetField().c - 1);
            v.emplace_back(GetField().r + 1, GetField().c + 1);
            v.emplace_back(GetField().r - 1, GetField().c + 1);
            v.emplace_back(GetField().r + 1, GetField().c - 1);
            for (int i = 0; i < v.size();)
            {
                if(v[i].r > 7 || v[i].r < 0 || v[i].c > 7 || v[i].c < 0)
                    v.erase(v.begin() + i);
                else
                    i++;
            }
            for (int i = 0; i < v.size();)
            {
                if (b->GetField(v[i]) != nullptr && b->GetField(v[i])->GetColor() == GetColor())
                    v.erase(v.begin() + i);
                else
                    i++;
            }

            if(ShortCastlingPossible(b))
                v.push_back(Cord(10, 10));
            if(LongCastlingPossible(b))
                v.push_back(Cord(11, 11));

            return v;

        }

        bool CheckMove(const MMove& m, const Board* b) const override
        {
            if(m.GetFrom().r == 10 && m.GetFrom().c == 10 && m.GetTo().r == 10 && m.GetTo().c == 10)
               return ShortCastlingPossible(b);
            if(m.GetFrom().r == 11 && m.GetFrom().c == 11 && m.GetTo().r == 11 && m.GetTo().c == 11)
               return LongCastlingPossible(b);
            vector<Cord> v = AllPossibleMoves(b);
            bool right_cord = false;

            for (int i = 0; i < 8; i++)
                if (m.GetTo().r == v[i].r && m.GetTo().c == v[i].c) { right_cord = true; break; }
            return right_cord;

        }
};
