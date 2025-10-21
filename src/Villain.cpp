#include "Villain.h"                    // Подключаем заголовочный файл класса Villain
#include <iostream>                     // Подключаем библиотеку для ввода-вывода

// Конструктор по умолчанию
Villain::Villain() : Base(),            // Вызываем конструктор базового класса
                     weaponType("Unknown"),  // Инициализируем тип оружия значением по умолчанию
                     crime("Unknown"),       // Инициализируем преступление значением по умолчанию
                     location("Unknown"),    // Инициализируем локацию значением по умолчанию
                     skills(nullptr),        // Инициализируем указатель на навыки как nullptr
                     skillsCount(0) {        // Инициализируем счетчик навыков нулем
    std::cout << "Villain default constructor called for: " << name << std::endl;  // Вывод отладочной информации
}

// Конструктор с параметрами
Villain::Villain(const std::string& name, const std::string& weapon, const std::string& crime,
    const std::string& location, const std::string* skillsArr, int count)
    : Base(name),                          // Вызываем конструктор базового класса с именем
      weaponType(weapon),                  // Инициализируем тип оружия переданным значением
      crime(crime),                        // Инициализируем преступление переданным значением
      location(location),                  // Инициализируем локацию переданным значением
      skillsCount(count) {                 // Инициализируем счетчик навыков переданным значением

    skills = new std::string[skillsCount]; // Выделяем память под массив навыков
    for (int i = 0; i < skillsCount; i++) {// Копируем каждый навык из переданного массива
        skills[i] = skillsArr[i];
    }
    std::cout << "Villain parameterized constructor called for: " << name << std::endl;  // Вывод отладочной информации
}

// Конструктор копирования
Villain::Villain(const Villain& other) : Base(other),           // Вызываем конструктор копирования базового класса
                                        weaponType(other.weaponType),  // Копируем тип оружия
                                        crime(other.crime),            // Копируем преступление
                                        location(other.location),      // Копируем локацию
                                        skillsCount(other.skillsCount) { // Копируем счетчик навыков
    skills = new std::string[skillsCount];  // Выделяем память под новый массив навыков
    for (int i = 0; i < skillsCount; i++) { // Копируем каждый навык из исходного объекта
        skills[i] = other.skills[i];
    }
    std::cout << "Villain copy constructor called for: " << name << std::endl;  // Вывод отладочной информации
}

// Деструктор
Villain::~Villain() {
    clearSkills();  // Освобождаем память, выделенную под навыки
    std::cout << "Villain destructor called for: " << name << std::endl;  // Вывод отладочной информации
}

// Метод для очистки массива навыков
void Villain::clearSkills() {
    delete[] skills;    // Освобождаем память, выделенную под массив навыков
    skills = nullptr;   // Обнуляем указатель
    skillsCount = 0;    // Сбрасываем счетчик навыков
}

// Перегрузка оператора присваивания
Villain& Villain::operator=(const Villain& other) {
    if (this != &other) {  // Проверка на самоприсваивание
        Base::operator=(other);  // Присваивание базовой части
        weaponType = other.weaponType;  // Копируем тип оружия
        crime = other.crime;            // Копируем преступление
        location = other.location;      // Копируем локацию
        skillsCount = other.skillsCount; // Копируем счетчик навыков

        clearSkills();                  // Очищаем текущие навыки
        skills = new std::string[skillsCount];  // Выделяем память под новые навыки
        for (int i = 0; i < skillsCount; i++) { // Копируем каждый навык
            skills[i] = other.skills[i];
        }
    }
    return *this;  // Возвращаем ссылку на текущий объект
}

// Метод для отображения информации о злодее
void Villain::display() const {
    std::cout << "=== Villain ===" << std::endl;  // Заголовок вывода
    std::cout << "Name: " << name << std::endl;   // Вывод имени
    std::cout << "Weapon Type: " << weaponType << std::endl;  // Вывод типа оружия
    std::cout << "Crime: " << crime << std::endl; // Вывод преступления
    std::cout << "Location: " << location << std::endl;  // Вывод локации
    std::cout << "Skills (" << skillsCount << "): ";  // Вывод количества навыков
    for (int i = 0; i < skillsCount; i++) {  // Перебор всех навыков
        std::cout << skills[i];              // Вывод текущего навыка
        if (i < skillsCount - 1) std::cout << ", ";  // Разделитель между навыками
    }
    std::cout << std::endl;  // Переход на новую строку
}

// Метод для редактирования злодея
void Villain::edit() {
    std::cout << "Editing Villain: " << name << std::endl;  // Сообщение о начале редактирования
    
    std::cout << "Enter new name: ";    // Запрос нового имени
    std::getline(std::cin, name);       // Чтение нового имени

    std::cout << "Enter weapon type: "; // Запрос типа оружия
    std::getline(std::cin, weaponType); // Чтение типа оружия

    std::cout << "Enter crime: ";       // Запрос преступления
    std::getline(std::cin, crime);      // Чтение преступления

    std::cout << "Enter location: ";    // Запрос локации
    std::getline(std::cin, location);   // Чтение локации

    std::cout << "Enter number of skills: ";  // Запрос количества навыков
    std::cin >> skillsCount;                  // Чтение количества навыков
    std::cin.ignore();                        // Очистка буфера ввода

    clearSkills();                            // Очистка старых навыков
    skills = new std::string[skillsCount];    // Выделение памяти под новые навыки

    for (int i = 0; i < skillsCount; i++) {   // Цикл для ввода каждого навыка
        std::cout << "Enter skill " << (i + 1) << ": ";  // Запрос навыка
        std::getline(std::cin, skills[i]);    // Чтение навыка
    }
}

// Метод для получения типа объекта
std::string Villain::getType() const {
    return "Villain";  // Возвращаем строку с типом объекта
}

// Метод для сохранения в файл (бинарный формат)
void Villain::saveToFile(std::ofstream& file) const {
    // Сохраняем тип объекта
    std::string type = getType();  // Получаем тип объекта
    int typeLength = type.length();  // Получаем длину строки типа
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));  // Сохраняем длину типа
    file.write(type.c_str(), typeLength);  // Сохраняем сам тип

    // Сохраняем имя
    int nameLength = name.length();  // Получаем длину имени
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));  // Сохраняем длину имени
    file.write(name.c_str(), nameLength);  // Сохраняем само имя

    // Сохраняем тип оружия
    int weaponLength = weaponType.length();  // Получаем длину типа оружия
    file.write(reinterpret_cast<const char*>(&weaponLength), sizeof(weaponLength));  // Сохраняем длину
    file.write(weaponType.c_str(), weaponLength);  // Сохраняем тип оружия

    // Сохраняем преступление
    int crimeLength = crime.length();  // Получаем длину преступления
    file.write(reinterpret_cast<const char*>(&crimeLength), sizeof(crimeLength));  // Сохраняем длину
    file.write(crime.c_str(), crimeLength);  // Сохраняем преступление

    // Сохраняем локацию
    int locationLength = location.length();  // Получаем длину локации
    file.write(reinterpret_cast<const char*>(&locationLength), sizeof(locationLength));  // Сохраняем длину
    file.write(location.c_str(), locationLength);  // Сохраняем локацию

    // Сохраняем количество навыков
    file.write(reinterpret_cast<const char*>(&skillsCount), sizeof(skillsCount));  // Сохраняем счетчик

    // Сохраняем каждый навык
    for (int i = 0; i < skillsCount; i++) {  // Перебираем все навыки
        int skillLength = skills[i].length();  // Получаем длину текущего навыка
        file.write(reinterpret_cast<const char*>(&skillLength), sizeof(skillLength));  // Сохраняем длину
        file.write(skills[i].c_str(), skillLength);  // Сохраняем сам навык
    }
}

// Метод для загрузки из файла (бинарный формат)
void Villain::loadFromFile(std::ifstream& file) {
    // Загружаем имя
    int nameLength;  // Переменная для хранения длины имени
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));  // Читаем длину имени
    char* nameBuffer = new char[nameLength + 1];  // Выделяем буфер для имени
    file.read(nameBuffer, nameLength);  // Читаем имя в буфер
    nameBuffer[nameLength] = '\0';  // Добавляем нулевой терминатор
    name = nameBuffer;  // Присваиваем имя
    delete[] nameBuffer;  // Освобождаем буфер

    // Загружаем тип оружия
    int weaponLength;  // Переменная для хранения длины типа оружия
    file.read(reinterpret_cast<char*>(&weaponLength), sizeof(weaponLength));  // Читаем длину
    char* weaponBuffer = new char[weaponLength + 1];  // Выделяем буфер
    file.read(weaponBuffer, weaponLength);  // Читаем тип оружия
    weaponBuffer[weaponLength] = '\0';  // Добавляем терминатор
    weaponType = weaponBuffer;  // Присваиваем тип оружия
    delete[] weaponBuffer;  // Освобождаем буфер

    // Загружаем преступление
    int crimeLength;  // Переменная для хранения длины преступления
    file.read(reinterpret_cast<char*>(&crimeLength), sizeof(crimeLength));  // Читаем длину
    char* crimeBuffer = new char[crimeLength + 1];  // Выделяем буфер
    file.read(crimeBuffer, crimeLength);  // Читаем преступление
    crimeBuffer[crimeLength] = '\0';  // Добавляем терминатор
    crime = crimeBuffer;  // Присваиваем преступление
    delete[] crimeBuffer;  // Освобождаем буфер

    // Загружаем локацию
    int locationLength;  // Переменная для хранения длины локации
    file.read(reinterpret_cast<char*>(&locationLength), sizeof(locationLength));  // Читаем длину
    char* locationBuffer = new char[locationLength + 1];  // Выделяем буфер
    file.read(locationBuffer, locationLength);  // Читаем локацию
    locationBuffer[locationLength] = '\0';  // Добавляем терминатор
    location = locationBuffer;  // Присваиваем локацию
    delete[] locationBuffer;  // Освобождаем буфер

    // Загружаем количество навыков
    file.read(reinterpret_cast<char*>(&skillsCount), sizeof(skillsCount));  // Читаем счетчик навыков

    // Загружаем навыки
    clearSkills();  // Очищаем текущие навыки
    skills = new std::string[skillsCount];  // Выделяем память под новые навыки
    for (int i = 0; i < skillsCount; i++) {  // Перебираем все навыки
        int skillLength;  // Переменная для хранения длины навыка
        file.read(reinterpret_cast<char*>(&skillLength), sizeof(skillLength));  // Читаем длину навыка
        char* skillBuffer = new char[skillLength + 1];  // Выделяем буфер для навыка
        file.read(skillBuffer, skillLength);  // Читаем навык
        skillBuffer[skillLength] = '\0';  // Добавляем терминатор
        skills[i] = skillBuffer;  // Сохраняем навык
        delete[] skillBuffer;  // Освобождаем буфер
    }
}

// Get/Set методы Villain
std::string Villain::getWeaponType() const { return weaponType; }  // Получить тип оружия
void Villain::setWeaponType(const std::string& weapon) { weaponType = weapon; }  // Установить тип оружия
std::string Villain::getCrime() const { return crime; }  // Получить преступление
void Villain::setCrime(const std::string& crime) { this->crime = crime; }  // Установить преступление
std::string Villain::getLocation() const { return location; }  // Получить локацию
void Villain::setLocation(const std::string& location) { this->location = location; }  // Установить локацию
std::string* Villain::getSkills() const { return skills; }  // Получить массив навыков
int Villain::getSkillsCount() const { return skillsCount; }  // Получить количество навыков
void Villain::setSkills(const std::string* skillsArr, int count) {  // Установить навыки
    clearSkills();  // Очистить текущие навыки
    skillsCount = count;  // Установить новое количество
    skills = new std::string[skillsCount];  // Выделить память
    for (int i = 0; i < skillsCount; i++) {  // Скопировать каждый навык
        skills[i] = skillsArr[i];
    }
}
