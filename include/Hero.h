#ifndef HERO_H                    // Защита от повторного включения файла
#define HERO_H                    // Определение макроса HERO_H

#include "Base.h"                 // Включение базового класса

class Hero : public Base {        // Объявление класса Hero, наследуемого от Base
private:                          // Секция приватных членов класса
    std::string weaponType;       // Тип оружия героя (строка)
    std::string* skills;          // Указатель на массив навыков (динамическая память)
    int skillsCount;              // Количество навыков в массиве

public:                           // Секция публичных методов
    Hero();                       // Конструктор по умолчанию
    Hero(const std::string& name, const std::string& weapon, const std::string* skillsArr, int count); // Конструктор с параметрами
    Hero(const Hero& other);      // Конструктор копирования
    ~Hero() override;             // Деструктор с переопределением

    Hero& operator=(const Hero& other); // Оператор присваивания

    void display() const override;     // Метод отображения информации (виртуальный)
    void edit() override;              // Метод редактирования (виртуальный)
    std::string getType() const override; // Метод получения типа объекта (виртуальный)

    // Методы для работы с файлами
    void saveToFile(std::ofstream& file) const override;  // Сохранение в файл
    void loadFromFile(std::ifstream& file) override;      // Загрузка из файла

    // Get/Set методы
    std::string getWeaponType() const;         // Получение типа оружия
    void setWeaponType(const std::string& weapon); // Установка типа оружия

    std::string* getSkills() const;            // Получение массива навыков
    int getSkillsCount() const;                // Получение количества навыков
    void setSkills(const std::string* skillsArr, int count); // Установка навыков

private:                         // Приватные вспомогательные методы
    void clearSkills();          // Очистка массива навыков (освобождение памяти)
};

#endif                           // Конец защиты от повторного включения
