#ifndef VILLAIN_H                    // Защита от повторного включения файла
#define VILLAIN_H                    // Определение макроса для защиты

#include "Base.h"                    // Подключение базового класса

class Villain : public Base {        // Объявление класса Villain, наследуемого от Base
private:                             // Секция приватных членов класса
    std::string weaponType;          // Тип оружия злодея
    std::string crime;               // Описание преступления
    std::string location;            // Место обитания/локация
    std::string* skills;             // Указатель на массив навыков (динамическая память)
    int skillsCount;                 // Количество навыков в массиве

public:                              // Секция публичных методов
    Villain();                       // Конструктор по умолчанию
    Villain(const std::string& name, const std::string& weapon, const std::string& crime,
        const std::string& location, const std::string* skillsArr, int count); // Конструктор с параметрами
    Villain(const Villain& other);   // Конструктор копирования
    ~Villain() override;             // Деструктор с переопределением

    Villain& operator=(const Villain& other); // Оператор присваивания

    void display() const override;   // Метод отображения информации (переопределен)
    void edit() override;            // Метод редактирования данных (переопределен)
    std::string getType() const override; // Метод получения типа объекта (переопределен)

    // Методы для работы с файлами
    void saveToFile(std::ofstream& file) const override; // Сохранение в файл (переопределен)
    void loadFromFile(std::ifstream& file) override;     // Загрузка из файла (переопределен)

    // Get/Set методы
    std::string getWeaponType() const;     // Получение типа оружия
    void setWeaponType(const std::string& weapon); // Установка типа оружия

    std::string getCrime() const;          // Получение описания преступления
    void setCrime(const std::string& crime); // Установка описания преступления

    std::string getLocation() const;       // Получение локации
    void setLocation(const std::string& location); // Установка локации

    std::string* getSkills() const;        // Получение массива навыков
    int getSkillsCount() const;            // Получение количества навыков
    void setSkills(const std::string* skillsArr, int count); // Установка навыков

private:                            // Приватные вспомогательные методы
    void clearSkills();             // Очистка массива навыков (освобождение памяти)
};

#endif                              // Конец защиты от повторного включения
