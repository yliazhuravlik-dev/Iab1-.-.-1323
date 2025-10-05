// Защита от повторного включения заголовочного файла,предотвращает ошибки компиляции при множественном включении одного файла
#ifndef HERO_H
#define HERO_H

// Подключаем заголовок базового класса
#include "Base.h"

// Подключаем стандартную библиотеку строк
#include <string>

// Подключаем стандартный контейнер vector
#include <vector>

// Объявление класса Hero, который наследует от абстрактного класса Base
class Hero : public Base {
private:
    // Поле для хранения имени героя, использует std::string для динамического управления памятью
    std::string name;
    
    // Поле для хранения типа оружия героя
    std::string weaponType;
    
    // Динамический массив для хранения навыков героя, std::vector автоматически управляет памятью
    std::vector<std::string> skills;

// Секция public - доступна извне класса
public:
    // Конструктор по умолчанию, инициализирует поля значениями по умолчанию
    Hero();
    
    // Конструктор с параметрами, принимает имя и тип оружия для инициализации
    Hero(const std::string& name, const std::string& weapon);
    
    // Конструктор копирования, создает новый объект как копию существующего
    Hero(const Hero& other);
    
    // Деструктор: ключевое слово override указывает, что метод переопределяет базовый
    ~Hero() override;

    // Set-метод для установки имени: override указывает на переопределение виртуального метода из Base
    void setName(const std::string& name) override;
    
    // Get-метод для получения имени: const означает, что метод не изменяет состояние объекта
    std::string getName() const override;
    
    // Set-метод для установки типа оружия
    void setWeaponType(const std::string& weapon);
    
    // Get-метод для получения типа оружия
    std::string getWeaponType() const;
    
    // Метод для добавления навыка в массив skills, принимает строку с названием навыка
    void addSkill(const std::string& skill);
    
    // Метод для удаления навыка по индексу: может генерировать исключение при неверном индексе
    void removeSkill(int index);
    
    // Метод для получения количества навыков: возвращает размер вектора skills
    int getSkillsCount() const;
    
    // Метод для получения навыка по индексу: const версия - только для чтения
    const std::string& getSkill(int index) const;

    // Реализация чисто виртуального метода из Base: выводит информацию о герое в консоль
    void print() const override;
    
    // Реализация чисто виртуального метода из Base: сохраняет данные героя в файл
    void saveToFile(std::ofstream& out) const override;
    
    // Реализация чисто виртуального метода из Base: загружает данные героя из файла
    void loadFromFile(std::ifstream& in) override;

    // Перегрузка оператора присваивания: обеспечивает корректное копирование объектов
    Hero& operator=(const Hero& other);
};

#endif
