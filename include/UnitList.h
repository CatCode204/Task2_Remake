#ifndef _H_UNITLIST_H_
#define _H_UNITLIST_H_

#include "Infantry.h"
#include "Vehicle.h"

class UnitList {
private:
    struct UnitNode {
        Unit* unit {nullptr};
        UnitNode* next {nullptr};
        UnitNode(Unit* unit) : unit(unit) {}
    };
    int capacity,size {0};
    UnitNode* head {nullptr};

public:
    UnitList(int capacity);
    ~UnitList();
    bool insert(Unit *unit);
    bool remove(Unit* unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    string str() const;

    int getEXP() const;
    int getLF() const;

    std::vector<Unit*> getUnits() const;
};

#endif
