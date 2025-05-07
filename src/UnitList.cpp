#include "UnitList.h"

constexpr int SPECIAL_CAPACITY = 12;
constexpr int DEFAULT_CAPACITY = 8;

bool isBaseOf(int n,int base) {
    int mul {1};
    while (mul * base <= n) mul *= base;
    while (n > 0) {
        if (n - mul >= 0) n -= mul;
        if (mul == 1) break;
        mul /= base;
    }
    return n == 0;
}

UnitList::UnitList(int S) {
    static constexpr int numBaseEvenPrime {3};
    static int baseEvenPrime[numBaseEvenPrime] {3,5,7};
    bool checkBaseEvenPrime {false};
    for (int i=0;i < numBaseEvenPrime;++i)
        if (isBaseOf(S,baseEvenPrime[i]))
            checkBaseEvenPrime = true;
    if (checkBaseEvenPrime)
        capacity = SPECIAL_CAPACITY;
    else
        capacity = DEFAULT_CAPACITY;
}

UnitList::~UnitList() {
    UnitNode* node {head};
    while (node) {
        UnitNode* tmpNode {node};
        node = node->next;
        //delete tmpNode->unit;
        delete tmpNode;
    }
}

bool UnitList::insert(Unit *unit) {
    if (unit == nullptr) return false;

    if (head == nullptr && size + 1 <= capacity) 
        return head = new UnitNode(unit),++size,true;

    for (UnitNode* node{head};node;node=node->next)
        if (node->unit == unit) return false;

    if (dynamic_cast<Infantry *>(unit)) {
        Infantry* infantryUnit = (Infantry*)unit;
        for (UnitNode *node{head}; node != nullptr; node = node->next)
            if (dynamic_cast<Infantry *>(node->unit)) {
                Infantry* infantryNodeUnit = (Infantry*)node->unit;
                if (infantryNodeUnit->getInfantryType() == infantryUnit->getInfantryType())
                    return infantryNodeUnit->setQuantity(infantryUnit->getQuantity() + infantryNodeUnit->getQuantity()),true;
            }
    } else {
        Vehicle* vehicleUnit = (Vehicle*)unit;
        for (UnitNode *node{head}; node != nullptr;node = node->next)
            if (dynamic_cast<Vehicle*>(node->unit)) {
                Vehicle* vehicleNodeUnit = (Vehicle*)node->unit;
                if (vehicleNodeUnit->getVehicleType() == vehicleUnit->getVehicleType())
                    return vehicleNodeUnit->setQuantity(vehicleUnit->getQuantity() + vehicleNodeUnit->getQuantity()),true;
            }
    }

    if (size + 1 > capacity) return false;

    ++size;
    if (dynamic_cast<Infantry*>(unit)) { // Nếu là lính thì thêm đầu danh sách
        UnitNode* newNode {new UnitNode(unit)};
        newNode->next = head;
        head = newNode;
    } else { // Nếu là phương tiện thì thêm vào cuối danh sách
        UnitNode* node {head};
        for (;node->next;node=node->next);
        node->next = new UnitNode(unit);
    }
    return true;
}

bool UnitList::remove(Unit* unit) {
    if (head->unit == unit) {
        --size;
        UnitNode* tmpNode {head};
        head = head->next;
        delete tmpNode;
        return true;
    }

    for (UnitNode* node{head};node;node = node->next)
        if (node->next->unit == unit) {
            --size;
            UnitNode* tmpNode = node->next;
            node->next = tmpNode->next;
            delete tmpNode;
            return true;
        }
    
    return false;
}

bool UnitList::isContain(VehicleType vehicleType) {
    for (UnitNode* node {head};node;node=node->next)
        if (dynamic_cast<Vehicle*>(node->unit) && ((Vehicle*)node->unit)->getVehicleType() == vehicleType) return true;
    return false;
}

bool UnitList::isContain(InfantryType infantryType) {
    for (UnitNode* node{head};node;node=node->next)
        if (dynamic_cast<Infantry*>(node->unit) && ((Infantry*)node->unit)->getInfantryType() == infantryType) return true;
    return false;
}

string UnitList::str() const {
    int countVehicle {0}, countInfantry{0};
    for (UnitNode* node{head};node;node=node->next)
        if (dynamic_cast<Infantry*>(node->unit)) 
            ++countInfantry;
        else
            ++countVehicle;
    
    std::stringstream out;
    out << "UnitList["
        << "count_vehicle=" << countVehicle << ';'
        << "count_infantry=" << countInfantry;
    if (head) out << ';';
    for (UnitNode* node{head};node;node=node->next) {
        out << node->unit->str();
        if (node->next) out << ',';
    }
    out << ']';
    return out.str();
}

int UnitList::getLF() const {
    int rt {0};
    for (UnitNode* node{head};node;node=node->next)
        if (dynamic_cast<Vehicle*>(node->unit)) rt += node->unit->getAttackScore();
    return rt;
}

int UnitList::getEXP() const {
    int rt {0};
    for (UnitNode* node{head};node;node=node->next)
        if (dynamic_cast<Infantry*>(node->unit)) rt += node->unit->getAttackScore();
    return rt;
}

std::vector<Unit*> UnitList::getUnits() const {
    std::vector<Unit*> ans;
    for (UnitNode* node{head};node;node=node->next)
        ans.push_back(node->unit);
    return ans;
}