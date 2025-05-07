#ifndef INFANTRY_H
#define INFANTRY_H

#include "Unit.h"

enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Infantry : public Unit
{
protected:
    InfantryType infantryType;  // * Thể loại bộ binh

public:
    Infantry(int quantity, int weight, Position pos, InfantryType infantryType);
    int getAttackScore() override;
    string str() const override;
    InfantryType getInfantryType() const;

    void UpdatePowerAttrib();
};

#endif // INFANTRY_H