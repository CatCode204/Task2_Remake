#include "Army.h"

constexpr int MIN_LF = 0;
constexpr int MAX_LF = 1000;
constexpr int MIN_EXP = 0;
constexpr int MAX_EXP = 500;

Army::Army(Unit **unitArray, int size, string name) : name(name) {
    int sumInfantryScore{0}, sumVehicleScore{0};
    for (int i=0;i < size;++i)
        if (dynamic_cast<Infantry*>(unitArray[i]))
            sumInfantryScore += unitArray[i]->getAttackScore();
        else
            sumVehicleScore += unitArray[i]->getAttackScore();
    
    int S{sumInfantryScore + sumVehicleScore};

    unitList = new UnitList(S);

    for (int i=0;i < size;++i)
        unitList->insert(unitArray[i]);
    
    setEXP(sumInfantryScore);
    setLF(sumVehicleScore);
}

Army::~Army() {
    delete unitList;
}

int Army::getEXP() const {
    return EXP;
}

int Army::getLF() const {
    return LF;
}

std::vector<Unit*> Army::getUnits() const {
    return unitList->getUnits();
}

UnitList* Army::getUnitList() const {
    return unitList;
}

void Army::setLF(const int& LF) {
    this->LF = clamp(LF,MIN_LF,MAX_LF);
}

void Army::setEXP(const int& EXP) {
    this->EXP = clamp(EXP,MIN_EXP,MAX_EXP);
}

void Army::updatePower() {
    int newEXP{0}, newLF{0};
    std::vector<Unit*> units = getUnits();
    for (std::size_t i = 0;i < units.size();++i)
        if (dynamic_cast<Infantry*>(units[i]))
            newEXP+= units[i]->getAttackScore();
        else
            newLF += units[i]->getAttackScore();
    
    setEXP(newEXP);
    setLF(newLF);
}