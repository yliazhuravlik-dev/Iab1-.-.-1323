#ifndef VILLAIN_H
#define VILLAIN_H

// Подключаем заголовок базового класса
#include "Base.h"

// Подключаем стандартную библиотеку строк
#include <string>

// Подключаем стандартный контейнер vector
#include <vector>

// Класс Villain (Злодей) наследует от абстрактного класса Base
class Villain : public Base {
private:
    // Поле для хранения имени злодея
    std::string name;
    
    // Поле для хранения типа оружия злодея
    std::string weaponType;
    
    // Поле для хранения описания злодеяния
    std::string crime;
    
    // Поле для хранения места обитания/локации злодея
    std::string location;
    
    // Динамический массив для хранения навыков злодея
    std::vector<std::string> skills;

public:
    // Конструктор по умолчанию
    Villain();
    
    // Конструктор с параметрами
    Villain(const std::string& name, const std::string& weapon, 
            const std::string& crime, const std::string& location);
    
    // Конструктор копирования
    Villain(const Villain& other);
    
    // Деструктор
    ~Villain() override;

    // Set/Get методы для имени (переопределенные из Base)
    void setName(const std::string& name) override;
    std::string getName() const override;
    
    // Set/Get методы для типа оружия
    void setWeaponType(const std::string& weapon);
    std::string getWeaponType() const;
    
    // Set/Get методы для злодеяния
    void setCrime(const std::string& crime);
    std::string getCrime() const;
    
    // Set/Get методы для локации
    void setLocation(const std::string& location);
    std::string getLocation() const;
    
    // Методы для работы с навыками
    void addSkill(const std::string& skill);
    void removeSkill(int index);
    int getSkillsCount() const;
    const std::string& getSkill(int index) const;

    // Реализация виртуальных методов из Base
    void print() const override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;

    // Перегрузка оператора присваивания
    Villain& operator=(const Villain& other);
};

#endif
