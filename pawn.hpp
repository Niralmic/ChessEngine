#pragma once
#include <iostream>
#include <vector>
#include "structures.hpp"
#include "figure.hpp"
#include "board.hpp"
#include "move.hpp"

using FigureTypeId = char;

class Pawn : public Figure
{
    public:
        Pawn(Cord field, Color color) : Figure(field, color) {}

        virtual FigureTypeId GetType() const override
        {
            return 'p';
        }

        bool EnPassantPossible(const Board* b, Cord from, Cord to) const
        {
            if (GetColor() == White) // если пешка которая бьет на проходе - белая
            {
                if(from.r != 3) // если пешка не стоит на 5 горизонтали
                    return false;
                Cord ep1(to.r + 1, to.c); // тут стоит черная пешка
                if(b->GetField(ep1) == nullptr || b->GetField(ep1)->GetType() != 'p' || b->GetField(ep1)->GetColor() == White) // если на поле ниже координаты куда стоит не пешка
                    return false;
                Cord ep2(1, to.c); // отсюда черная пешка должна ходить чтобы взятие на проходе было возможно(7 горизонталь)
                if(b->GetField(ep2) != nullptr) // если на 7 горизонтали стоит какая-то фигура, то черная пешка не могла оттуда ходить и взятие на проходе не возможно
                    return false;
                Cord to2;
                Cord from2 = b->GetLastMoveCords(to2);
                if(to2.r != ep1.r || to2.c != ep1.c || from2.r != ep2.r || from2.c != ep2.c)
                    return false;
                return true;

            }
            // пешка черная
            if(from.r != 4) // если пешка не стоит на 4 горизонтали
                return false;
            Cord ep1(to.r - 1, to.c); // тут стоит белая пешка
            if(b->GetField(ep1) == nullptr || b->GetField(ep1)->GetType() != 'p' || b->GetField(ep1)->GetColor() == Black) // если на поле ниже координаты куда стоит не пешка
                return false;
            Cord ep2(6, to.c); // отсюда белая пешка должна ходить чтобы взятие на проходе было возможно(2 горизонталь)
            if(b->GetField(ep2) != nullptr) // если на 2 горизонтали стоит какая-то фигура, то черная пешка не могла оттуда ходить и взятие на проходе не возможно
                return false;
            Cord to2;
            Cord from2 = b->GetLastMoveCords(to2);
            if(to2.r != ep1.r || to2.c != ep1.c || from2.r != ep2.r || from2.c != ep2.c)
                return false;
            return true;
        }

        vector<Cord> AllPossibleMoves(const Board* b) const override
        {
            vector<Cord> v;
            vector<Cord> res;
            if (GetColor() == White)
            {
                if(EnPassantPossible(b, Cord(GetField().r, GetField().c), Cord(GetField().r - 1, GetField().c + 1)))
                    res.emplace_back(GetField().r - 1, GetField().c + 1);
                if(EnPassantPossible(b, Cord(GetField().r, GetField().c), Cord(GetField().r - 1, GetField().c - 1)))
                    res.emplace_back(GetField().r - 1, GetField().c - 1);
                v.emplace_back(GetField().r - 1, GetField().c - 1);
                v.emplace_back(GetField().r - 1, GetField().c);
                v.emplace_back(GetField().r - 1, GetField().c + 1);
                v.emplace_back(GetField().r - 2, GetField().c);
                for (int i = 0; i < v.size(); i++)
                    if(v[i].r > 7 || v[i].r < 0 || v[i].c > 7 || v[i].c < 0)
                        v[i] = Cord(-1, -1);
                for(int i = 0; i < v.size(); i++)
                {
                    if (i == 0)
                    {
                        if(v[i].r != -1)
                        {
                            Figure* f = b->GetField(v[i]).get();
                            if(f != nullptr && f->GetColor() != White)
                                res.emplace_back(v[i]);
                        }

                    }

                    if (i == 2)
                    {
                        if(v[i].r != -1)
                        {
                            Figure* f = b->GetField(v[i]).get();
                            if(f != nullptr && f->GetColor() != White)
                                res.emplace_back(v[i]);
                        }

                    }

                    if (i == 1)
                    {
                        if(v[i].r != -1)
                        {
                            Figure* f = b->GetField(v[i]).get();
                            if(f == nullptr)
                                res.emplace_back(v[i]);
                        }
                    }
                    if(i == 3)
                    {
                        if(v[i].r != -1)
                        {
                            if (GetField().r == 6)
                            {
                                Figure* f = b->GetField(Cord(GetField().r - 1, GetField().c)).get();
                                Figure* f2 = b->GetField(Cord(GetField().r - 2, GetField().c)).get();
                                if(f == nullptr || f2 == nullptr)
                                    res.emplace_back(v[i]);
                            }

                        }
                    }

                }

                return res;
            }
            if(EnPassantPossible(b, Cord(GetField().r, GetField().c), Cord(GetField().r + 1, GetField().c + 1)))
                res.emplace_back(GetField().r + 1, GetField().c + 1);
            if(EnPassantPossible(b, Cord(GetField().r, GetField().c), Cord(GetField().r + 1, GetField().c - 1)))
                res.emplace_back(GetField().r + 1, GetField().c - 1);
            v.emplace_back(GetField().r + 1, GetField().c - 1);
            v.emplace_back(GetField().r + 1, GetField().c);
            v.emplace_back(GetField().r + 1, GetField().c + 1);
            v.emplace_back(GetField().r + 2, GetField().c);
            for(int i = 0; i < v.size(); i++)
                if(v[i].r > 7 || v[i].r < 0 || v[i].c > 7 || v[i].c < 0)
                    v[i] = Cord(-1, -1);

            for(int i = 0; i < v.size(); i++)
            {
                if (i == 0)
                {
                    if(v[i].r != -1)
                    {
                        Figure* f = b->GetField(v[i]).get();
                        if(f != nullptr && f->GetColor() != Black)
                            res.emplace_back(v[i]);
                    }

                }

                if (i == 2)
                {
                    if(v[i].r != -1)
                    {
                        Figure* f = b->GetField(v[i]).get();
                        if(f != nullptr && f->GetColor() != Black)
                            res.emplace_back(v[i]);
                    }

                }

                if (i == 1)
                {
                    if(v[i].r != -1)
                    {
                        Figure* f = b->GetField(v[i]).get();
                        if(f == nullptr)
                            res.emplace_back(v[i]);
                    }
                }
                if(i == 3)
                {
                    if(v[i].r != -1)
                    {
                        if (GetField().r == 1)
                        {
                            Figure* f = b->GetField(Cord(GetField().r + 1, GetField().c)).get();
                            Figure* f2 = b->GetField(Cord(GetField().r + 2, GetField().c)).get();
                            if(f == nullptr || f2 == nullptr)
                                res.emplace_back(v[i]);
                        }

                    }
                }

            }

                return res;
        }

        bool CheckMove(const MMove& m, const Board* b) const override
        {
            int i;
            bool right_cord = false;
            std::vector<Cord> v = AllPossibleMoves(b);
            for (i = 0; i < v.size(); i++)
                if (m.GetTo().r == v[i].r && m.GetTo().c == v[i].c) { right_cord = true; break; }
            return right_cord;
        }
        bool CouldTake(const MMove& m, const Board* b) const override // могла бы пешка взять на этом поле(для роккировки)
        {
            if(GetColor() == White)
            {
                if(m.GetTo().c == m.GetFrom().c + 1 && m.GetTo().r == m.GetFrom().r - 1)
                    return true;
                if(m.GetTo().c == m.GetFrom().c - 1 && m.GetTo().r == m.GetFrom().r - 1)
                    return true;
                return false;
            }
            if(m.GetTo().c == m.GetFrom().c + 1 && m.GetTo().r == m.GetFrom().r + 1)
                return true;
            if(m.GetTo().c == m.GetFrom().c - 1 && m.GetTo().r == m.GetFrom().r + 1)
                return true;
            return false;

        }
};
