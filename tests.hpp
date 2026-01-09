#pragma once
#include "Chess.hpp"
#include <cassert>

using namespace std;
using FigureTypeId = char;

void TestStaleMate()
{
    Chess test;
    test.SetFigureOnBoard('K', Cord(7, 4), White);
    test.SetFigureOnBoard('K', Cord(0, 4), Black);
    test.SetFigureOnBoard('r', Cord(1, 3), White);
    test.SetFigureOnBoard('r', Cord(1, 5), White);
    test.SetZug(Black);
    unique_ptr<Figure> nptr = nullptr;
    Cord from(0, 4);
    Cord to(0, 3);
    MMove m(from, to, move(nptr));
    FigureTypeId promote = '0';
    test.CMove(move(m), promote);
    assert(promote == 'S');
}

void TestCheckMate()
{
    Chess test1;
    test1.SetFigureOnBoard('K', Cord(7, 4), White);
    test1.SetFigureOnBoard('K', Cord(0, 4), Black);
    test1.SetFigureOnBoard('r', Cord(0, 7), White);
    test1.SetFigureOnBoard('r', Cord(1, 0), White);
    test1.SetZug(Black);
    unique_ptr<Figure> nptr1 = nullptr;
    Cord from1(0, 4);
    Cord to1(0, 3);
    MMove m1(from1, to1, move(nptr1));
    FigureTypeId promote1 = '0';
    test1.CMove(move(m1), promote1);
    assert(promote1 == 'W');

    Chess test2;
    test2.SetFigureOnBoard('K', Cord(7, 4), Black);
    test2.SetFigureOnBoard('K', Cord(0, 4), White);
    test2.SetFigureOnBoard('r', Cord(0, 7), Black);
    test2.SetFigureOnBoard('r', Cord(1, 0), Black);
    test2.SetZug(White);
    unique_ptr<Figure> nptr2 = nullptr;
    Cord from2(0, 4);
    Cord to2(0, 3);
    MMove m2(from2, to2, move(nptr2));
    FigureTypeId promote2 = '0';
    test2.CMove(move(m2), promote2);
    assert(promote2 == 'B');
}

void TestCheckMateByLongCastling()
{
    Chess test1;
    test1.SetFigureOnBoard('K', Cord(7, 4), White);
    test1.SetFigureOnBoard('K', Cord(7, 7), Black);
    test1.SetFigureOnBoard('r', Cord(7, 0), White);
    test1.SetFigureOnBoard('r', Cord(6, 0), White);
    test1.SetZug(White);
    unique_ptr<Figure> nptr1 = nullptr;
    Cord from1(11, 11);
    Cord to1(11, 11);
    MMove m1(from1, to1, move(nptr1));
    FigureTypeId promote1 = '0';
    assert(test1.CMove(move(m1), promote1));
    assert(promote1 == 'W');

    Chess test2;
    test2.SetFigureOnBoard('K', Cord(0, 4), Black);
    test2.SetFigureOnBoard('K', Cord(0, 7), White);
    test2.SetFigureOnBoard('r', Cord(0, 0), Black);
    test2.SetFigureOnBoard('r', Cord(1, 0), Black);
    test2.SetZug(Black);
    unique_ptr<Figure> nptr2 = nullptr;
    Cord from2(11, 11);
    Cord to2(11, 11);
    MMove m2(from2, to2, move(nptr2));
    FigureTypeId promote2 = '0';
    assert(test2.CMove(move(m2), promote2));
    assert(promote2 == 'B');
}

void TestCheckMateByShortCastling()
{
    Chess test1;
    test1.SetFigureOnBoard('K', Cord(7, 4), White);
    test1.SetFigureOnBoard('K', Cord(7, 0), Black);
    test1.SetFigureOnBoard('r', Cord(7, 7), White);
    test1.SetFigureOnBoard('r', Cord(6, 7), White);
    test1.SetZug(White);
    unique_ptr<Figure> nptr1 = nullptr;
    Cord from1(10, 10);
    Cord to1(10, 10);
    MMove m1(from1, to1, move(nptr1));
    FigureTypeId promote1 = '0';
    assert(test1.CMove(move(m1), promote1));
    assert(promote1 == 'W');

    Chess test2;
    test2.SetFigureOnBoard('K', Cord(0, 4), Black);
    test2.SetFigureOnBoard('K', Cord(0, 0), White);
    test2.SetFigureOnBoard('r', Cord(0, 7), Black);
    test2.SetFigureOnBoard('r', Cord(1, 7), Black);
    test2.SetZug(Black);
    unique_ptr<Figure> nptr2 = nullptr;
    Cord from2(10, 10);
    Cord to2(10, 10);
    MMove m2(from2, to2, move(nptr2));
    FigureTypeId promote2 = '0';
    assert(test2.CMove(move(m2), promote2));
    assert(promote2 == 'B');
}

void TestEnPassantWhite()
{
    Chess test1;
    test1.SetFigureOnBoard('K', Cord(7, 4), White);
    test1.SetFigureOnBoard('K', Cord(0, 4), Black);
    test1.SetFigureOnBoard('p', Cord(3, 4), White);
    test1.SetFigureOnBoard('p', Cord(1, 3), Black);
    test1.SetZug(Black);
    unique_ptr<Figure> nptr1 = nullptr;
    Cord from1(1, 3);
    Cord to1(3, 3);
    MMove m1(from1, to1, move(nptr1));
    FigureTypeId promote1 = '0';
    test1.CMove(move(m1), promote1);
    from1.r = 3;
    from1.c = 4;
    to1.r = 2;
    to1.c = 3;
    unique_ptr<Figure> nptr12 = nullptr;
    MMove m2(from1, to1, move(nptr12));
    assert(test1.CMove(move(m2), promote1));

    Chess test2;
    test2.SetFigureOnBoard('K', Cord(7, 4), White);
    test2.SetFigureOnBoard('K', Cord(0, 4), Black);
    test2.SetFigureOnBoard('p', Cord(3, 4), White);
    test2.SetFigureOnBoard('p', Cord(1, 5), Black);
    test2.SetZug(Black);
    unique_ptr<Figure> nptr2 = nullptr;
    Cord from2(1, 5);
    Cord to2(3, 5);
    MMove m3(from2, to2, move(nptr2));
    test2.CMove(move(m3), promote1);
    from1.r = 3;
    from1.c = 4;
    to1.r = 2;
    to1.c = 5;
    unique_ptr<Figure> nptr13 = nullptr;
    MMove m4(from1, to1, move(nptr13));
    assert(test2.CMove(move(m4), promote1));
}

void TestEnPassantBlack()
{
    Chess test1;
    test1.SetFigureOnBoard('K', Cord(7, 4), White);
    test1.SetFigureOnBoard('K', Cord(0, 4), Black);
    test1.SetFigureOnBoard('p', Cord(6, 4), White);
    test1.SetFigureOnBoard('p', Cord(4, 3), Black);
    test1.SetZug(White);
    unique_ptr<Figure> nptr1 = nullptr;
    Cord from1(6, 4);
    Cord to1(4, 4);
    MMove m1(from1, to1, move(nptr1));
    FigureTypeId promote1 = '0';
    test1.CMove(move(m1), promote1);
    from1.r = 4;
    from1.c = 3;
    to1.r = 5;
    to1.c = 4;
    unique_ptr<Figure> nptr12 = nullptr;
    MMove m2(from1, to1, move(nptr12));
    assert(test1.CMove(move(m2), promote1));

    Chess test2;
    test2.SetFigureOnBoard('K', Cord(7, 4), White);
    test2.SetFigureOnBoard('K', Cord(0, 4), Black);
    test2.SetFigureOnBoard('p', Cord(6, 4), White);
    test2.SetFigureOnBoard('p', Cord(4, 5), Black);
    test2.SetZug(White);
    unique_ptr<Figure> nptr2 = nullptr;
    Cord from2(6, 4);
    Cord to2(4, 4);
    MMove m3(from2, to2, move(nptr2));
    test2.CMove(move(m3), promote1);
    from1.r = 4;
    from1.c = 5;
    to1.r = 5;
    to1.c = 4;
    unique_ptr<Figure> nptr13 = nullptr;
    MMove m4(from1, to1, move(nptr13));
    assert(test2.CMove(move(m4), promote1));
}
void DoTests()
{
    TestStaleMate();
    TestCheckMate();
    TestEnPassantWhite();
    TestEnPassantBlack();
    TestCheckMateByLongCastling();
    TestCheckMateByShortCastling();
}
