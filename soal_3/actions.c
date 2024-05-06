#include <stdio.h>
#include <string.h>

const char* checkGap(float gap) {
    if (gap < 3.5) return "Gogogo";
    else if (gap <= 10) return "Push";
    else return "Stay out of trouble";
}

const char* checkFuel(float fuel) {
    if (fuel > 80) return "Push Push Push";
    else if (fuel > 50) return "You can go";
    else return "Conserve Fuel";
}

const char* checkTire(int tireWear) {
    if (tireWear > 80) return "Go Push Go Push";
    else if (tireWear > 50) return "Good Tire Wear";
    else if (tireWear >= 30) return "Conserve Your Tire";
    else return "Box Box Box";
}

const char* tireChange(const char* tireType) {
    if (strcmp(tireType, "Soft") == 0) return "Mediums Ready";
    else if (strcmp(tireType, "Medium") == 0) return "Box for Softs";
    return "Unknown Tire Type";
}
