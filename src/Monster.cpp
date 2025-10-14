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

Monster::~Monster() {
    // Вывод информации о вызове деструктора
    std::cout << "Monster destructor for " << name << std::endl;
}

void Monster::setName(const std::string& name) {
    // this->name обращается к полю класса (чтобы отличить от параметра)
    this->name = name;
}

std::string Monster::getName() const {
    // Возвращаем копию строки name
    return name;
}

void Monster::setAppearance(const std::string& appearance) {
    this->appearance = appearance;
}

std::string Monster::getAppearance() const {
    return appearance;
}

void Monster::print() const {
    std::cout << "Monster: " << name << std::endl;
    std::cout << "Appearance: " << appearance << std::endl;
    std::cout << "-------------------" << std::endl;
}

void Monster::saveToFile(std::ofstream& out) const {
    out << "Monster\n";
    out << name << "\n";
    out << appearance << "\n";
}

void Monster::loadFromFile(std::ifstream& in) {
    std::getline(in, name);
    std::getline(in, appearance);
}

Monster& Monster::operator=(const Monster& other) {
    if (this != &other) {
        name = other.name;
        appearance = other.appearance;
    }
    return *this;
}
