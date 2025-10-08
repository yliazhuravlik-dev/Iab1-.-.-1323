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
    skills.push_back(skill);
}

void Villain::removeSkill(int index) {
    // Проверяем валидность индекса
    if (index >= 0 && index < skills.size()) {
        skills.erase(skills.begin() + index);
    } else {
        throw std::out_of_range("Invalid skill index for removal in Villain.");
    }
}
int Villain::getSkillsCount() const {
    // size() возвращает текущее количество элементов в векторе
    return skills.size();
}
const std::string& Villain::getSkill(int index) const {
    if (index >= 0 && index < skills.size()) {

        return skills[index];
    } else {
        throw std::out_of_range("Invalid skill index in Villain.");
    }
}

void Villain::print() const {
    std::cout << "Villain: " << name << std::endl;
    std::cout << "Weapon: " << weaponType << std::endl;
    std::cout << "Crime: " << crime << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Skills: ";

    if (skills.empty()) {
        std::cout << "No skills";
    } else {
        for (size_t i = 0; i < skills.size(); ++i) {
            std::cout << skills[i];
            if (i != skills.size() - 1) {
                std::cout << "; ";
            }
        }
    }
    std::cout << "\n-------------------" << std::endl;
}
void Villain::saveToFile(std::ofstream& out) const {
    out << "Villain\n";
    out << name << "\n";
    out << weaponType << "\n";
    out << crime << "\n";
    out << location << "\n";
    out << skills.size() << "\n";
    
    for (const auto& skill : skills) {
        out << skill << "\n";
    }
}

void Villain::loadFromFile(std::ifstream& in) {
    std::getline(in, name);
    std::getline(in, weaponType);
    std::getline(in, crime);
    std::getline(in, location);
    
    int skillCount;
    in >> skillCount;
    in.ignore();
    
    skills.clear();
    
    std::string skill;
    for (int i = 0; i < skillCount; ++i) {
        std::getline(in, skill);
        skills.push_back(skill);
    }
}

Villain& Villain::operator=(const Villain& other) {
    if (this != &other) {
        name = other.name;
        weaponType = other.weaponType;
        crime = other.crime;
        location = other.location;
        skills = other.skills;
    }
    return *this;
}
