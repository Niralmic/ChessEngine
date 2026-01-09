#pragma once
#include"structures.hpp"
#include"figure.hpp"

class Bishop : public Figure // слон
{
    public:
        Bishop(Cord field, Color color) : Figure(field, color) {}
        virtual FigureTypeId GetType() const override
        {
            return 'b';
        }
        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            int i = 0;
            std::vector<Cord> v;
            Cord mbmove(GetField().r + 1, GetField().c + 1); //
            while(mbmove.c <= 7 && mbmove.r <= 7 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи вправо
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.c++;
                mbmove.r++;
            }
            mbmove.c = GetField().c - 1;
            mbmove.r = GetField().r - 1;
            while(mbmove.c >= 0 && mbmove.r >= 0 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи влево
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.c--;
                mbmove.r--;
            }
            mbmove.c = GetField().c - 1;
            mbmove.r = GetField().r + 1;
            while(mbmove.r <= 7 && mbmove.c >= 0 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи вниз
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.r++;
                mbmove.c--;
            }
            mbmove.r = GetField().r - 1;
            mbmove.c = GetField().c + 1;
            while(mbmove.r >= 0 && (b->GetField(mbmove) == nullptr || b->GetField(mbmove)->GetColor() != GetColor())) // все ходы ладьи вверх
            {
                if(b->GetField(mbmove) != nullptr && b->GetField(mbmove)->GetColor() != GetColor())
                {
                   v.push_back(mbmove);
                   break;
                }
                v.push_back(mbmove);
                mbmove.r--;
                mbmove.c++;
            }
            return v;
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
