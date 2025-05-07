#ifndef UNIT_H
#define UNIT_H

#include "Position.h"

class Unit {
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos);
    ~Unit() = default;
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;

    int getQuantity() const;
    int getWeight() const;

    void setQuantity(int quantity);
    void setWeight(int weight);

    friend class UnitList;
};

#endif // UNIT_H
