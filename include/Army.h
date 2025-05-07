#ifndef _H_ARMY_H_
#define _H_ARMY_H_

#include "UnitList.h"
using namespace std;

class Army {
protected:
    int LF;        // * Tổng điểm từ các phương tiện (Vehicle)
    int EXP;       // * Tổng điểm từ các lực lượng bộ binh (Infantry)
    UnitList *unitList;
    string name;
    
public:
    Army(Unit **unitArray, int size, string name);
    ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    int getLF() const;
    int getEXP() const;
    std::vector<Unit*> getUnits() const;
    UnitList* getUnitList() const;

protected:
    virtual void attack(Army* enemy) = 0;
    virtual void defense(Army* enemy) = 0;
    void setLF(const int& LF);
    void setEXP(const int& EXP);
    void updatePower();
};

#endif
