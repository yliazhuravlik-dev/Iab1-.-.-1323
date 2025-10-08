// Подключаем заголовочный файл класса Villain
#include "Villain.h"

// Подключаем библиотеку для работы с вводом-выводом
#include <iostream>

// Подключаем библиотеку для работы с исключениями
#include <stdexcept>

// Конструктор по умолчанию
// Инициализирует все поля значениями по умолчанию
Villain::Villain() 
    : name("Unknown"), 
      weaponType("None"), 
      crime("Unknown crime"), 
      location("Unknown location") {
    // Вывод отладочной информации в консоль
    std::cout << "Villain default constructor for " << name << std::endl;
}

// Конструктор с параметрами, принимает имя, оружие, злодеяние и локацию для инициализации
Villain::Villain(const std::string& name, const std::string& weapon, 
                 const std::string& crime, const std::string& location)
    : name(name), 
      weaponType(weapon), 
      crime(crime), 
      location(location) {
    // Список инициализации устанавливает значения всех полей
    std::cout << "Villain parametrized constructor for " << name << std::endl;
}

// Конструктор копирования, создает глубокую копию объекта other
Villain::Villain(const Villain& other)
    : name(other.name),
      weaponType(other.weaponType),
      crime(other.crime),
      location(other.location),
      skills(other.skills) {
    // Копируем все поля из other в новый объект
    std::cout << "Villain copy constructor for " << name << std::endl;
}

// Деструктор, автоматически вызывается при удалении объекта
Villain::~Villain() {
    // Вектор skills автоматически освобождает свою память
    std::cout << "Villain destructor for " << name << std::endl;
}

// Set-метод для установки имени
void Villain::setName(const std::string& name) {
    // this->name обращается к полю класса (чтобы отличить от параметра)
    this->name = name;
}

// Get-метод для получения имени
std::string Villain::getName() const {
    // Возвращаем копию строки name
    return name;
}

// Set-метод для установки типа оружия
void Villain::setWeaponType(const std::string& weapon) {
    this->weaponType = weapon;
}

// Get-метод для получения типа оружия
std::string Villain::getWeaponType() const {
    return weaponType;
}

// Set-метод для установки злодеяния
void Villain::setCrime(const std::string& crime) {
    this->crime = crime;
}

// Get-метод для получения злодеяния
std::string Villain::getCrime() const {
    return crime;
}

// Set-метод для установки локации
void Villain::setLocation(const std::string& location) {
    this->location = location;
}

// Get-метод для получения локации
std::string Villain::getLocation() const {
    return location;
}

// Метод для добавления навыка
void Villain::addSkill(const std::string& skill) {
    // Метод push_back добавляет элемент в конец вектора skills
    skills.push_back(skill);
}

// Метод для удаления навыка по индексу
void Villain::removeSkill(int index) {
    // Проверяем валидность индекса
    if (index >= 0 && index < skills.size()) {
        // Удаляем элемент по указанному индексу: skills.begin() - итератор на начало вектора
        skills.erase(skills.begin() + index);
    } else {
        // Генерируем исключение при неверном индексе
        throw std::out_of_range("Invalid skill index for removal in Villain.");
    }
}

// Метод для получения количества навыков
int Villain::getSkillsCount() const {
    // size() возвращает текущее количество элементов в векторе
    return skills.size();
}

// Метод для получения навыка по индексу (только для чтения)
const std::string& Villain::getSkill(int index) const {
    // Проверяем валидность индекса
    if (index >= 0 && index < skills.size()) {
        // Возвращаем константную ссылку на строку (без копирования)
        return skills[index];
    } else {
        throw std::out_of_range("Invalid skill index in Villain.");
    }
}

// Метод для вывода информации о злодее
void Villain::print() const {
    // Выводим основную информацию о злодее
    std::cout << "Villain: " << name << std::endl;
    std::cout << "Weapon: " << weaponType << std::endl;
    std::cout << "Crime: " << crime << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Skills: ";
    
    // Проверяем, есть ли навыки
    if (skills.empty()) {
        std::cout << "No skills";
    } else {
        // Проходим по всем навыкам и выводим их
        for (size_t i = 0; i < skills.size(); ++i) {
            std::cout << skills[i];
            // Добавляем разделитель, кроме последнего элемента
            if (i != skills.size() - 1) {
                std::cout << "; ";
            }
        }
    }
    std::cout << "\n-------------------" << std::endl;
}

// Метод для сохранения данных в файл
void Villain::saveToFile(std::ofstream& out) const {
    // Записываем идентификатор типа для последующей загрузки
    out << "Villain\n";
    // Записываем имя (перевод строки как разделитель)
    out << name << "\n";
    // Записываем тип оружия
    out << weaponType << "\n";
    // Записываем злодеяние
    out << crime << "\n";
    // Записываем локацию
    out << location << "\n";
    // Записываем количество навыков
    out << skills.size() << "\n";
    
    // Записываем каждый навык на отдельной строке
    for (const auto& skill : skills) {
        out << skill << "\n";
    }
}

// Метод для загрузки данных из файла
void Villain::loadFromFile(std::ifstream& in) {
    // Считываем имя (getline читает до символа новой строки)
    std::getline(in, name);
    // Считываем тип оружия
    std::getline(in, weaponType);
    // Считываем злодеяние
    std::getline(in, crime);
    // Считываем локацию
    std::getline(in, location);
    
    // Считываем количество навыков
    int skillCount;
    in >> skillCount;
    // Игнорируем символ новой строки после числа
    in.ignore();
    
    // Очищаем текущий список навыков
    skills.clear();
    
    // Временная переменная для считывания навыков
    std::string skill;
    for (int i = 0; i < skillCount; ++i) {
        // Считываем каждый навык
        std::getline(in, skill);
        // Добавляем в вектор
        skills.push_back(skill);
    }
}

// Перегрузка оператора присваивания
Villain& Villain::operator=(const Villain& other) {
    // Проверка на самоприсваивание (a = a)
    if (this != &other) {
        // Копируем все поля из other
        name = other.name;
        weaponType = other.weaponType;
        crime = other.crime;
        location = other.location;
        skills = other.skills;  // Вектор поддерживает оператор =
    }
    // Возвращаем ссылку на текущий объект
    return *this;
}
