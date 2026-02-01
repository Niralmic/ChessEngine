#pragma once
#include <cstdint>
#include "structures.hpp"


class State
{
    private:
        uint8_t _white;
        uint8_t _black;
    public:
        State() : _white(StateWhite(0)), _black(StateBlack(0)) {}
        void CheckWhite(){_white |= checkWhite;}
        void CheckmateWhite(){_white |= checkmateWhite;}
        void StalemateWhite(){_white |= stalemateWhite;}
        void CastlingMadeWhite(){_white |= castlingMadeWhite;}
        void CheckBlack(){_black |= checkBlack;}
        void CheckmateBlack(){_black |= checkmateBlack;}
        void StalemateBlack(){_black |= stalemateBlack;}
        void CastlingMadeBlack(){_black |= castlingMadeBlack;}
        void NoCheckWhite(){_white &= ~checkWhite;}
        void NoCheckmateWhite(){_white &= ~checkmateWhite;}
        void NoStalemateWhite(){_white &= ~stalemateWhite;}
        void NoCastlingMadeWhite(){_white &= ~castlingMadeWhite;}
        void NoCheckBlack(){_black &= ~checkBlack;}
        void NoCheckmateBlack(){_black &= ~checkmateBlack;}
        void NoStalemateBlack(){_black &= ~stalemateBlack;}
        void NoCastlingMadeBlack(){_black &= ~castlingMadeBlack;}
        void ClearWhite(){_white = 0;}
        void ClearBlack(){_black = 0;}
        bool IsCheckWhite() const {return _white & checkWhite;}
        bool IsCheckmateWhite() const {return _white & checkmateWhite;}
        bool IsStalemateWhite() const {return _white & stalemateWhite;}
        bool IsCastlingMadeWhite() const {return _white & castlingMadeWhite;}
        bool IsCheckBlack() const {return _black & checkBlack;}
        bool IsCheckmateBlack() const {return _black & checkmateBlack;}
        bool IsStalemateBlack() const {return _black & stalemateBlack;}
        bool IsCastlingMadeBlack() const {return _black & castlingMadeBlack;}

};
