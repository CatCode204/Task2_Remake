#include "Infantry.h"

constexpr int FIGHTING_YEAR = 1975;

bool isSquareNumber(int n) {
    int sqrtN = sqrt(n);
    return sqrtN * sqrtN == n;
}

int sumDigits(int n) {
    return n ? n % 10 + sumDigits(n / 10) : 0;
}

int computePersonalNumber(int score, int year) {
    int rt {sumDigits(score) + sumDigits(year)};
    for (;rt / 10;rt = sumDigits(rt));
    return rt;
}

//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------
Infantry::Infantry(int quantity, int weight, Position pos, InfantryType infantryType)
    : Unit(quantity, weight, pos), infantryType(infantryType) {
    UpdatePowerAttrib();
}

int Infantry::getAttackScore() {
    return infantryType * 56 + quantity * weight;
}

string infantryTypeEnumToString(InfantryType type) {
    if (type == InfantryType::ANTIAIRCRAFTSQUAD) return "ANTIAIRCRAFTSQUAD";
    if (type == InfantryType::ENGINEER) return "ENGINEER";
    if (type == InfantryType::MORTARSQUAD) return "MOTARSQUAD";
    if (type == InfantryType::REGULARINFANTRY) return "REGULARINFANTRY";
    if (type == InfantryType::SNIPER) return "SNIPER";
    return "SPECIALFORCES";
}

string Infantry::str() const {
    stringstream out;
    out << "Infantry["
        << "infantryType=" << infantryTypeEnumToString(infantryType) << ','
        << "quantity=" << quantity << ','
        << "weight=" << weight << ','
        << "position=" << pos.str() << ']';
    return out.str();
}

InfantryType Infantry::getInfantryType() const {
    return infantryType;
}

void Infantry::UpdatePowerAttrib() {
    int score = getAttackScore();
    if (infantryType == InfantryType::SPECIALFORCES && isSquareNumber(this->weight))
        score += 75;
    int personalNumber = computePersonalNumber(score,FIGHTING_YEAR);
    if (personalNumber > 7)
        this->quantity = ceil(quantity * 1.2f);
    else if (personalNumber < 3)
        this->quantity = ceil(quantity * 0.9f);
}