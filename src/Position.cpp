#include "Position.h"

Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const string &str_pos) {
    sscanf(str_pos.c_str(),"(%d,%d)",&r,&c);
}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { this->r = r; }
void Position::setCol(int c) { this->c = c; }
string Position::str() const {
    std::stringstream out;
    out << '(' << r << ',' << c << ')';
    return out.str();
}