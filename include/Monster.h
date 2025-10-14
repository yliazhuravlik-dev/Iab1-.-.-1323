// Защита от повторного включения заголовочного файла
#ifndef MONSTER_H
#define MONSTER_H

// Подключаем заголовок базового класса
#include "Base.h"

// Подключаем стандартную библиотеку строк
#include <string>

// Класс Monster (Монстр) наследует от абстрактного класса Base
// Для монстра определено наименование и описание внешнего вида
class Monster : public Base {
private:
    // Поле для хранения наименования монстра
    std::string name;
    
    // Поле для хранения описания внешнего вида монстра
    std::string appearance;

public:
    // Конструктор по умолчанию
    Monster();
    
    // Конструктор с параметрами
    Monster(const std::string& name, const std::string& appearance);
    
    // Конструктор копирования
    Monster(const Monster& other);
    
    // Деструктор
    ~Monster() override;

    // Set/Get методы для имени (переопределенные из Base)
    void setName(const std::string& name) override;
    std::string getName() const override;
    
    // Set/Get методы для описания внешнего вида
    void setAppearance(const std::string& appearance);
    std::string getAppearance() const;

    // Реализация виртуальных методов из Base
    void print() const override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;

    // Перегрузка оператора присваивания
    Monster& operator=(const Monster& other);
};

#endif
