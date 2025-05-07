#ifndef _H_LIBERATIONARMY_H_
#define _H_LIBERATIONARMY_H_

#include "Army.h"

class LiberationArmy : public Army {
public:
    LiberationArmy(Unit **unitArray, int size, string name);
    void fight(Army *enemy, bool defense) override;
    string str() const override;

protected:
    void attack(Army* enemy) override;
    void defense(Army* enemy) override;

private:
    void winUpdate(std::vector<Unit*> teamA,std::vector<Unit*> teamB,Army* enemy);
    void noCombatUpdate();

    static int nearestFibonacci(int value);
    static vector<Unit*> findMinSetGeqMaxScore(vector<Unit*> units, int maxScore);
};

#endif