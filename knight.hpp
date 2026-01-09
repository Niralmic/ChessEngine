#pragma once
#include"structures.hpp"
#include"figure.hpp"
class Knight : public Figure // конь
{
    public:
        Knight(Cord field, Color color) : Figure(field, color) {}

        virtual FigureTypeId GetType() const override
        {
            return 'k';
        }

        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            vector<Cord> v;
            vector<Cord> res;
            v.emplace_back(GetField().r - 2, GetField().c + 1);
            v.emplace_back(GetField().r - 1, GetField().c + 2);
            v.emplace_back(GetField().r + 1, GetField().c + 2);
            v.emplace_back(GetField().r + 2, GetField().c + 1);
            v.emplace_back(GetField().r + 2, GetField().c - 1);
            v.emplace_back(GetField().r + 1, GetField().c - 2);
            v.emplace_back(GetField().r - 1, GetField().c - 2);
            v.emplace_back(GetField().r - 2, GetField().c - 1);
            for (int i = 0; i < v.size(); i++)
                if(v[i].r > 7 || v[i].r < 0 || v[i].c > 7 || v[i].c < 0)
                    v[i] = Cord(-1, -1);
            for(int i = 0; i < v.size(); i++)
            {
                if(v[i].r != -1)
                {
                    Figure* f = b->GetField(v[i]).get();
                    if(f == nullptr)
                        res.emplace_back(v[i]);
                    else
                    {
                        if(f->GetColor() != GetColor())
                            res.emplace_back(v[i]);
                    }

                }
            }
            return res;
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

