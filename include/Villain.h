
#ifndef VILLAIN_H
#define VILLAIN_H

#include "Base.h"
#include <string>
#include <vector>


class Villain : public Base {
private:
    std::string name;
    std::string weaponType;
    std::string crime;
    std::string location;
    std::vector<std::string> skills;

public:

    Villain();
    
    Villain(const std::string& name, const std::string& weapon, 
            const std::string& crime, const std::string& location);
    
    Villain(const Villain& other);
    
    ~Villain() override;

    void setName(const std::string& name) override;
    std::string getName() const override;
    
    void setWeaponType(const std::string& weapon);
    std::string getWeaponType() const;
    
    void setCrime(const std::string& crime);
    std::string getCrime() const;
    
    void setLocation(const std::string& location);
    std::string getLocation() const;
    
    void addSkill(const std::string& skill);
    void removeSkill(int index);
    int getSkillsCount() const;
    const std::string& getSkill(int index) const;

    void print() const override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;

    Villain& operator=(const Villain& other);
};

#endif
