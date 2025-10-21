#ifndef MONSTER_H                    // Защита от повторного включения файла
#define MONSTER_H                    // Определение макроса MONSTER_H

#include "Base.h"                    // Подключение базового класса

class Monster : public Base {        // Объявление класса Monster, наследуемого от Base
private:                             // Секция приватных членов класса
    std::string appearance;          // Приватное поле: описание внешнего вида монстра

public:                              // Секция публичных методов
    Monster();                       // Конструктор по умолчанию
    Monster(const std::string& name, const std::string& appearance); // Конструктор с параметрами
    Monster(const Monster& other);   // Конструктор копирования
    ~Monster() override;             // Деструктор с указанием переопределения

    Monster& operator=(const Monster& other); // Перегрузка оператора присваивания

    void display() const override;   // Переопределение метода display для вывода информации
    void edit() override;            // Переопределение метода edit для редактирования
    std::string getType() const override; // Переопределение метода getType для получения типа

    // Методы для работы с файлами
    void saveToFile(std::ofstream& file) const override;  // Сохранение в файл
    void loadFromFile(std::ifstream& file) override;      // Загрузка из файла

    // Get/Set методы
    std::string getAppearance() const;        // Get-метод для получения внешнего вида
    void setAppearance(const std::string& appearance); // Set-метод для установки внешнего вида
};

#endif                              // Конец блока защиты от повторного включения
