#include "Unit.h"

//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
Unit::Unit(int quantity, int weight, Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{}
Position Unit::getCurrentPosition() const {
    return this->pos;
}

int Unit::getWeight() const {
    return weight;
}

int Unit::getQuantity() const {
    return quantity;
}

void Unit::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Unit::setWeight(int weight) {
    this->weight = weight;
}