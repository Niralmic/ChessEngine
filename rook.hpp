#pragma once
#include"structures.hpp"
#include"figure.hpp"

class Rook : public Figure // ладья
{
    public:
        Rook(Cord field, Color color) : Figure(field, color) {}
        virtual FigureTypeId GetType() const override
        {
            return 'r';
        }

        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            int i = 0;
            std::vector<Cord> v;
            Cord mbmove(GetField().r, GetField().c + 1); //
            while (mbmove.c <= 7 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor()))
            {
                if (b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                    v.push_back(mbmove);
                    break;
                }
                v.push_back(mbmove);
                mbmove.c++;
            }

            mbmove.c = GetField().c - 1;
            while(mbmove.c >= 0 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи влево
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.c--;
            }
            mbmove.c = GetField().c;
            mbmove.r = GetField().r + 1;
            while(mbmove.r <= 7 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи вниз
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.r++;
            }
            mbmove.r = GetField().r - 1;
            while(mbmove.r >= 0 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи вверх
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.r--;
            }
            return v;
        }

        bool CheckMove(const MMove& m, const Board* b) const override
        {
            bool right_cord = false;
            vector<Cord> v = AllPossibleMoves(b);

            for (int i = 0; i < v.size(); i++) // если корды "to" есть в векторе, значит ход корректен
                if (m.GetTo().r == v[i].r && m.GetTo().c == v[i].c) { right_cord = true; break; }
            return right_cord;
        }

};

