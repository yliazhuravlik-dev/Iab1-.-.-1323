#include "Monster.h"
#include <iostream>

Monster::Monster() : name("Unknown Monster"), appearance("Terrifying appearance") {
    std::cout << "Monster default constructor for " << name << std::endl;
}

Monster::Monster(const std::string& name, const std::string& appearance)
    : name(name), appearance(appearance) {
    std::cout << "Monster parametrized constructor for " << name << std::endl;
}


Monster::Monster(const Monster& other)
    : name(other.name), appearance(other.appearance) {
    std::cout << "Monster copy constructor for " << name << std::endl;
}

