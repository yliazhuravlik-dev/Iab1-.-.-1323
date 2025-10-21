#include "Hero.h"                    // Подключение заголовочного файла класса Hero
#include <iostream>                  // Подключение библиотеки для ввода/вывода

// Конструктор по умолчанию
Hero::Hero() : Base(), weaponType("Unknown"), skills(nullptr), skillsCount(0) {
    std::cout << "Hero default constructor called for: " << name << std::endl;  // Вывод отладочной информации
}

// Конструктор с параметрами
Hero::Hero(const std::string& name, const std::string& weapon, const std::string* skillsArr, int count)
    : Base(name), weaponType(weapon), skillsCount(count) {  // Инициализация базового класса и полей

    skills = new std::string[skillsCount];                  // Выделение памяти для массива навыков
    for (int i = 0; i < skillsCount; i++) {                // Копирование навыков из переданного массива
        skills[i] = skillsArr[i];
    }
    std::cout << "Hero parameterized constructor called for: " << name << std::endl;  // Отладочный вывод
}

// Конструктор копирования
Hero::Hero(const Hero& other) : Base(other), weaponType(other.weaponType), skillsCount(other.skillsCount) {
    skills = new std::string[skillsCount];                  // Выделение памяти для нового массива
    for (int i = 0; i < skillsCount; i++) {                // Копирование навыков из другого объекта
        skills[i] = other.skills[i];
    }
    std::cout << "Hero copy constructor called for: " << name << std::endl;  // Отладочный вывод
}

// Деструктор
Hero::~Hero() {
    clearSkills();                                          // Очистка динамической памяти
    std::cout << "Hero destructor called for: " << name << std::endl;  // Отладочный вывод
}

// Метод для очистки массива навыков
void Hero::clearSkills() {
    delete[] skills;                                        // Освобождение памяти массива
    skills = nullptr;                                       // Обнуление указателя
    skillsCount = 0;                                        // Сброс счетчика
}

// Перегрузка оператора присваивания
Hero& Hero::operator=(const Hero& other) {
    if (this != &other) {                                   // Проверка на самоприсваивание
        Base::operator=(other);                             // Вызов оператора присваивания базового класса
        weaponType = other.weaponType;                      // Копирование типа оружия
        skillsCount = other.skillsCount;                    // Копирование количества навыков

        clearSkills();                                      // Очистка старых навыков
        skills = new std::string[skillsCount];              // Выделение памяти для новых навыков
        for (int i = 0; i < skillsCount; i++) {            // Копирование навыков
            skills[i] = other.skills[i];
        }
    }
    return *this;                                           // Возврат ссылки на текущий объект
}

// Метод для вывода информации о герое
void Hero::display() const {
    std::cout << "=== Hero ===" << std::endl;               // Заголовок вывода
    std::cout << "Name: " << name << std::endl;             // Вывод имени
    std::cout << "Weapon Type: " << weaponType << std::endl; // Вывод типа оружия
    std::cout << "Skills (" << skillsCount << "): ";        // Вывод количества навыков
    for (int i = 0; i < skillsCount; i++) {                // Цикл по всем навыкам
        std::cout << skills[i];                             // Вывод текущего навыка
        if (i < skillsCount - 1) std::cout << ", ";        // Добавление разделителя (кроме последнего)
    }
    std::cout << std::endl;                                 // Перевод строки
}

// Метод для редактирования героя
void Hero::edit() {
    std::cout << "Editing Hero: " << name << std::endl;     // Сообщение о начале редактирования
    std::cout << "Enter new name: ";                        // Запрос нового имени
    std::getline(std::cin, name);                           // Чтение имени из консоли

    std::cout << "Enter weapon type: ";                     // Запрос типа оружия
    std::getline(std::cin, weaponType);                     // Чтение типа оружия

    std::cout << "Enter number of skills: ";                // Запрос количества навыков
    std::cin >> skillsCount;                                // Чтение количества навыков
    std::cin.ignore();                                      // Очистка буфера ввода

    clearSkills();                                          // Очистка старых навыков
    skills = new std::string[skillsCount];                  // Выделение памяти для новых навыков

    for (int i = 0; i < skillsCount; i++) {                // Цикл для ввода каждого навыка
        std::cout << "Enter skill " << (i + 1) << ": ";     // Запрос навыка
        std::getline(std::cin, skills[i]);                  // Чтение навыка
    }
}

// Метод для получения типа объекта
std::string Hero::getType() const {
    return "Hero";                                          // Возврат строки с типом объекта
}

// Метод для сохранения в файл (бинарный формат)
void Hero::saveToFile(std::ofstream& file) const {
    // Сохраняем тип объекта
    std::string type = getType();                           // Получение типа объекта
    int typeLength = type.length();                         // Длина строки типа
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));  // Запись длины типа
    file.write(type.c_str(), typeLength);                   // Запись самого типа

    // Сохраняем имя
    int nameLength = name.length();                         // Длина имени
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));  // Запись длины имени
    file.write(name.c_str(), nameLength);                   // Запись имени

    // Сохраняем тип оружия
    int weaponLength = weaponType.length();                 // Длина типа оружия
    file.write(reinterpret_cast<const char*>(&weaponLength), sizeof(weaponLength));  // Запись длины
    file.write(weaponType.c_str(), weaponLength);           // Запись типа оружия

    // Сохраняем количество навыков
    file.write(reinterpret_cast<const char*>(&skillsCount), sizeof(skillsCount));  // Запись количества

    // Сохраняем каждый навык
    for (int i = 0; i < skillsCount; i++) {                // Цикл по всем навыкам
        int skillLength = skills[i].length();               // Длина текущего навыка
        file.write(reinterpret_cast<const char*>(&skillLength), sizeof(skillLength));  // Запись длины
        file.write(skills[i].c_str(), skillLength);         // Запись навыка
    }
}

// Метод для загрузки из файла (бинарный формат)
void Hero::loadFromFile(std::ifstream& file) {
    // Загружаем имя
    int nameLength;                                         // Переменная для длины имени
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));  // Чтение длины имени
    char* nameBuffer = new char[nameLength + 1];           // Выделение буфера для имени
    file.read(nameBuffer, nameLength);                     // Чтение имени
    nameBuffer[nameLength] = '\0';                         // Добавление нуль-терминатора
    name = nameBuffer;                                     // Сохранение имени
    delete[] nameBuffer;                                   // Освобождение буфера

    // Загружаем тип оружия
    int weaponLength;                                      // Переменная для длины типа оружия
    file.read(reinterpret_cast<char*>(&weaponLength), sizeof(weaponLength));  // Чтение длины
    char* weaponBuffer = new char[weaponLength + 1];       // Выделение буфера
    file.read(weaponBuffer, weaponLength);                 // Чтение типа оружия
    weaponBuffer[weaponLength] = '\0';                     // Добавление нуль-терминатора
    weaponType = weaponBuffer;                             // Сохранение типа оружия
    delete[] weaponBuffer;                                 // Освобождение буфера

    // Загружаем количество навыков
    file.read(reinterpret_cast<char*>(&skillsCount), sizeof(skillsCount));  // Чтение количества навыков

    // Загружаем навыки
    clearSkills();                                          // Очистка старых навыков
    skills = new std::string[skillsCount];                  // Выделение памяти для новых навыков
    for (int i = 0; i < skillsCount; i++) {                // Цикл по всем навыкам
        int skillLength;                                    // Переменная для длины навыка
        file.read(reinterpret_cast<char*>(&skillLength), sizeof(skillLength));  // Чтение длины
        char* skillBuffer = new char[skillLength + 1];     // Выделение буфера для навыка
        file.read(skillBuffer, skillLength);               // Чтение навыка
        skillBuffer[skillLength] = '\0';                   // Добавление нуль-терминатора
        skills[i] = skillBuffer;                           // Сохранение навыка
        delete[] skillBuffer;                              // Освобождение буфера
    }
}

// Get-метод для типа оружия
std::string Hero::getWeaponType() const {
    return weaponType;                                      // Возврат типа оружия
}

// Set-метод для типа оружия
void Hero::setWeaponType(const std::string& weapon) {
    weaponType = weapon;                                    // Установка нового типа оружия
}

// Get-метод для массива навыков
std::string* Hero::getSkills() const {
    return skills;                                          // Возврат указателя на массив навыков
}

// Get-метод для количества навыков
int Hero::getSkillsCount() const {
    return skillsCount;                                     // Возврат количества навыков
}

// Set-метод для навыков
void Hero::setSkills(const std::string* skillsArr, int count) {
    clearSkills();                                          // Очистка старых навыков
    skillsCount = count;                                    // Установка нового количества
    skills = new std::string[skillsCount];                  // Выделение памяти
    for (int i = 0; i < skillsCount; i++) {                // Копирование новых навыков
        skills[i] = skillsArr[i];
    }
}
