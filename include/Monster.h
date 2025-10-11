#ifndef MONSTER_H
#define MONSTER_H

#include "Base.h"
#include <string>

class Monster : public Base {
private:
    std::string name;
    std::string appearance;

public:
    Monster();
    Monster(const std::string& name, const std::string& appearance);
    Monster(const Monster& other);
    ~Monster() override;
    void setName(const std::string& name) override;
    std::string getName() const override;
    void setAppearance(const std::string& appearance);
    std::string getAppearance() const;
    void print() const override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;
    Monster& operator=(const Monster& other);
};

#endif
