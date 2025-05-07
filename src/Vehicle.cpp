#include "Vehicle.h"

Vehicle::Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType)
    : Unit(quantity, weight, pos), vehicleType(vehicleType){}

int Vehicle::getAttackScore() {
    return ceil((vehicleType * 304 + quantity * weight) / 30.f);
}

string vehicleTypeEnumToString(VehicleType type) {
    if (type == VehicleType::ANTIAIRCRAFT) return "ANTIAIRCRAFT";
    if (type == VehicleType::APC) return "APC";
    if (type == VehicleType::ARMOREDCAR) return "ARMOREDCAR";
    if (type == VehicleType::ARTILLERY) return "ARTILLERY";
    if (type == VehicleType::MORTAR) return "MORTAR";
    if (type == VehicleType::TANK) return "TANK";
    return "TRUCK";
}

string Vehicle::str() const {
    std::stringstream out;
    out << "Vehicle["
        << "vehicleType=" << vehicleTypeEnumToString(vehicleType) << ','
        << "quantity=" << quantity << ','
        << "weight=" << weight << ','
        << "position=" << pos.str() << "]";        
    return out.str();
}

VehicleType Vehicle::getVehicleType() const {
    return vehicleType;
}