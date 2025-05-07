#include "ARVN.h"

// TODO: Implement
ARVN::ARVN(Unit** unitArray, int size, string name)
    : Army(unitArray, size, name) {}

void ARVN::fight(Army* enemy, bool defense) {
    return defense ? this->defense(enemy) : attack(enemy);
}

string ARVN::str() const {
    std::stringstream out;
    out << "ARVN["
        << "LF=" << LF << ','
        << "EXP=" << EXP << ','
        << "unitList=" << unitList->str() << ']';
    return out.str();
}

void ARVN::attack(Army* enemy) {
    std::vector<Unit*> units {getUnits()};
    for (std::size_t i = 0;i < units.size();++i)
        units[i]->setQuantity(ceil(units[i]->getQuantity() * 0.8f));
    for (std::size_t i = 0;i < units.size();++i)
        if (units[i]->getQuantity() == 1) unitList->remove(units[i]);
    updatePower();
}

void ARVN::defense(Army* enemy) {
    std::vector<Unit*> units{getUnits()};
    for (std::size_t i = 0;i < units.size();++i)
        units[i]->setWeight(ceil(units[i]->getWeight() * 0.8f));
    updatePower();
}