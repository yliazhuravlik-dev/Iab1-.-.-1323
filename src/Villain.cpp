#include "Villain.h"
#include <iostream>
#include <stdexcept>

Villain::Villain() 
    : name("Unknown"), 
      weaponType("None"), 
      crime("Unknown crime"), 
      location("Unknown location") {
    std::cout << "Villain default constructor for " << name << std::endl;
}
Villain::Villain(const std::string& name, const std::string& weapon, 
                 const std::string& crime, const std::string& location)
    : name(name), 
      weaponType(weapon), 
      crime(crime), 
      location(location) {
    std::cout << "Villain parametrized constructor for " << name << std::endl;
}

Villain::Villain(const Villain& other)
    : name(other.name),
      weaponType(other.weaponType),
      crime(other.crime),
      location(other.location),
      skills(other.skills) {
    std::cout << "Villain copy constructor for " << name << std::endl;
}

Villain::~Villain() {
    std::cout << "Villain destructor for " << name << std::endl;
}

void Villain::setName(const std::string& name) {
    this->name = name;
}

std::string Villain::getName() const {
    return name;
}

void Villain::setWeaponType(const std::string& weapon) {
    this->weaponType = weapon;
}

std::string Villain::getWeaponType() const {
    return weaponType;
}

void Villain::setCrime(const std::string& crime) {
    this->crime = crime;
}

std::string Villain::getCrime() const {
    return crime;
}

void Villain::setLocation(const std::string& location) {
    this->location = location;
}

std::string Villain::getLocation() const {
    return location;
}

void Villain::addSkill(const std::string& skill) {
    // Метод push_back добавляет элемент в конец вектора skills
    skills.push_back(skill);
}
