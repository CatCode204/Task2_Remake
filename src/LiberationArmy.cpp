#include "LiberationArmy.h"

LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name)
                                                : Army(unitArray,size,name) {}

void LiberationArmy::fight(Army *enemy, bool defense){
    return defense ? this->defense(enemy) : attack(enemy);
}

string LiberationArmy::str() const {
    std::stringstream out;
    out << "LiberationArmy["
        << "LF=" << LF << ','
        << "EXP=" << EXP << ','
        << "unitList=" << unitList->str() << ']';
    return out.str();
}

void LiberationArmy::attack(Army* enemy) {
    setLF(ceil(LF * 1.5f));
    setEXP(ceil(EXP * 1.5f));
    std::vector<Unit*> teamInfantry,teamVehicle;
    std::vector<Unit*> liberationUnits = unitList->getUnits();

    int enemyLF {enemy->getLF()};
    int enemyEXP {enemy->getEXP()};
    for (std::size_t i = 0;i < liberationUnits.size();++i)
        if (dynamic_cast<Infantry*>(liberationUnits[i]))
            teamInfantry.push_back(liberationUnits[i]); 
        else
            teamVehicle.push_back(liberationUnits[i]);
    
    std::vector<Unit*> teamA {LiberationArmy::findMinSetGeqMaxScore(teamInfantry,enemyEXP)};
    std::vector<Unit*> teamB {LiberationArmy::findMinSetGeqMaxScore(teamVehicle,enemyLF)};

    int numWinTeams {(teamA.size() > 0) + (teamB.size() > 0)};
    if (numWinTeams == 2) return winUpdate(teamA,teamB,enemy);

    if (numWinTeams == 1 && teamA.empty()) {
        if (EXP > enemyEXP) return winUpdate(teamA,teamB,enemy);
        return noCombatUpdate();
    }

    if (numWinTeams == 1 && teamB.empty()) {
        if (LF > enemyLF) return winUpdate(teamA,teamB,enemy);
        return noCombatUpdate();
    }

    return noCombatUpdate();
}

void LiberationArmy::defense(Army* enemy) {
    setLF(ceil(LF * 1.3f));
    setEXP(ceil(EXP * 1.3f));

    int numWinAttribs{(LF > enemy->getLF()) + (EXP > enemy->getEXP())};

    if (numWinAttribs == 2) return;

    if (numWinAttribs == 1) {
        std::vector<Unit*> units{getUnits()};
        for (std::size_t i = 0;i < units.size();++i)
            units[i]->setQuantity(ceil(units[i]->getQuantity() * 0.9f));
        return updatePower();
    } 

    std::vector<Unit*> units{getUnits()};
    for (std::size_t i = 0;i < units.size();++i)
        units[i]->setQuantity(nearestFibonacci(units[i]->getQuantity()));
    updatePower();
    defense(enemy);
}

void LiberationArmy::winUpdate(std::vector<Unit*> teamA,std::vector<Unit*> teamB, Army* enemy) {
    if (teamA.empty() || teamB.empty()) {
        std::vector<Unit*> units {getUnits()};
        if (teamA.empty())
            for (std::size_t i = 0;i < units.size();++i) 
                if (dynamic_cast<Infantry*>(units[i])) teamA.push_back(units[i]);
        if (teamB.empty())
            for (std::size_t i = 0;i < units.size();++i)
                if (dynamic_cast<Vehicle*>(units[i])) teamB.push_back(units[i]);
    }
    for (std::size_t i{0}; i < teamA.size(); ++i)
        unitList->remove(teamA[i]);
    for (std::size_t i{0}; i < teamB.size(); ++i)
        unitList->remove(teamB[i]);
    std::vector<Unit *> enemyUnits{enemy->getUnits()};
    for (int i = enemyUnits.size() - 1; i >= 0; --i)
        if (unitList->insert(enemyUnits[i])) {
            enemy->getUnitList()->remove(enemyUnits[i]);
            if (dynamic_cast<Infantry*>(enemyUnits[i]))
                ((Infantry*)enemyUnits[i])->UpdatePowerAttrib();
        }
    enemy->fight(this,true);
    updatePower();
    return;
}

void LiberationArmy::noCombatUpdate() {
    std::vector<Unit*> units = getUnits();
    for (std::size_t i{0};i < units.size();++i)
        units[i]->setWeight(ceil(units[i]->getWeight() * 0.9f));
    updatePower();
}

int LiberationArmy::nearestFibonacci(int value) {
    static vector<int> fibonancies({0,1});
    std::size_t l{0},r{fibonancies.size()};
    while (r - l > 1) {
        std::size_t m{l + r >> 1};
        if (fibonancies[m] > value) r = m;
        else l = m;
    }
    if (r < fibonancies.size()) return fibonancies[r];
    for (;fibonancies.back() <= value;)
        fibonancies.push_back(*fibonancies.rbegin() + *(fibonancies.rbegin() + 1));
    return fibonancies.back();
}

vector<Unit*> LiberationArmy::findMinSetGeqMaxScore(vector<Unit*> units, int maxScore) {
    int sumScore {0};
    for (std::size_t i{0};i < units.size();++i)
        sumScore += units[i]->getAttackScore();
    if (sumScore < maxScore) return std::vector<Unit*>();

    std::vector<bool> dp(sumScore + 5,false);
    std::vector<int> trace(sumScore + 5,-1);
    dp[0] = true;
    for (std::size_t i = 0;i < units.size();++i) {
        int score = units[i]->getAttackScore();
        for (int j = sumScore;j >= score;--j)
            if (!dp[j] && dp[j - score]) {
                dp[j] = true;
                trace[j] = i;
            }
    }

    int suitableScore {sumScore};
    for (int i=maxScore;i <= sumScore;++i)
        if (dp[i]) {
            suitableScore = i;
            break;
        }

    std::vector<Unit*> ans;
    while (suitableScore) {
        ans.push_back(units[trace[suitableScore]]);
        suitableScore -= units[trace[suitableScore]]->getAttackScore();
    }
    
    return ans;
}