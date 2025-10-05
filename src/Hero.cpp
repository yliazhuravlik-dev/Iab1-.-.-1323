// Подключаем заголовочный файл класса Hero
// Необходим для реализации методов класса
#include "Hero.h"

// Подключаем библиотеку для работы с вводом-выводом
// Используется для std::cout, std::endl
#include <iostream>

// Подключаем библиотеку для работы с исключениями
// Используется для std::out_of_range
#include <stdexcept>

// Конструктор по умолчанию
// Использует список инициализации для установки начальных значений
Hero::Hero() : name("Unknown"), weaponType("None") {
    // Вывод отладочной информации в консоль
    // Демонстрирует вызов конструктора (требование лабораторной)
    std::cout << "Hero default constructor for " << name << std::endl;
}

// Конструктор с параметрами
// Принимает имя и тип оружия, инициализирует поля
Hero::Hero(const std::string& name, const std::string& weapon) 
    : name(name), weaponType(weapon) {
    // Список инициализации: name(name) - инициализация поля name параметром name
    // Аналогично для weaponType(weapon)
    std::cout << "Hero parametrized constructor for " << name << std::endl;
}

// Конструктор копирования
// Создает глубокую копию объекта other
Hero::Hero(const Hero& other) 
    : name(other.name), 
      weaponType(other.weaponType), 
      skills(other.skills) {
    // Копируем все поля из other в новый объект
    // skills(other.skills) - копирует весь вектор навыков
    std::cout << "Hero copy constructor for " << name << std::endl;
}

// Деструктор
// Автоматически вызывается при удалении объекта
Hero::~Hero() {
    // Вектор skills автоматически освобождает свою память
    // Не требуется ручное удаление элементов
    std::cout << "Hero destructor for " << name << std::endl;
}

// Set-метод для установки имени
void Hero::setName(const std::string& name) {
    // this->name обращается к полю класса (чтобы отличить от параметра)
    this->name = name;
}

// Get-метод для получения имени
std::string Hero::getName() const {
    // Возвращаем копию строки name
    return name;
}

// Set-метод для установки типа оружия
void Hero::setWeaponType(const std::string& weapon) {
    this->weaponType = weapon;
}

// Get-метод для получения типа оружия
std::string Hero::getWeaponType() const {
    return weaponType;
}

// Метод для добавления навыка
void Hero::addSkill(const std::string& skill) {
    // Метод push_back добавляет элемент в конец вектора
    // Вектор автоматически увеличивает свой размер при необходимости
    skills.push_back(skill);
}

// Метод для удаления навыка по индексу
void Hero::removeSkill(int index) {
    // Проверяем валидность индекса
    if (index >= 0 && index < skills.size()) {
        // Удаляем элемент по указанному индексу
        // skills.begin() - итератор на начало вектора
        skills.erase(skills.begin() + index);
    } else {
        // Генерируем исключение при неверном индексе
        // std::out_of_range - стандартное исключение для выхода за границы
        throw std::out_of_range("Invalid skill index for removal.");
    }
}

// Метод для получения количества навыков
int Hero::getSkillsCount() const {
    // size() возвращает текущее количество элементов в векторе
    return skills.size();
}

// Метод для получения навыка по индексу (только для чтения)
const std::string& Hero::getSkill(int index) const {
    // Проверяем валидность индекса
    if (index >= 0 && index < skills.size()) {
        // Возвращаем константную ссылку на строку (без копирования)
        return skills[index];
    } else {
        throw std::out_of_range("Invalid skill index.");
    }
}

// Метод для вывода информации о герое
void Hero::print() const {
    // Выводим основную информацию о герое
    std::cout << "Hero: " << name << "\nWeapon: " << weaponType << "\nSkills: ";
    
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
void Hero::saveToFile(std::ofstream& out) const {
    // Записываем идентификатор типа для последующей загрузки
    out << "Hero\n";
    // Записываем имя (перевод строки как разделитель)
    out << name << "\n";
    // Записываем тип оружия
    out << weaponType << "\n";
    // Записываем количество навыков
    out << skills.size() << "\n";
    
    // Записываем каждый навык на отдельной строке
    for (const auto& skill : skills) {
        out << skill << "\n";
    }
}

// Метод для загрузки данных из файла
void Hero::loadFromFile(std::ifstream& in) {
    // Считываем имя (getline читает до символа новой строки)
    std::getline(in, name);
    // Считываем тип оружия
    std::getline(in, weaponType);
    
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
Hero& Hero::operator=(const Hero& other) {
    // Проверка на самоприсваивание (a = a)
    if (this != &other) {
        // Копируем все поля из other
        name = other.name;
        weaponType = other.weaponType;
        skills = other.skills;  // Вектор поддерживает оператор =
    }
    // Возвращаем ссылку на текущий объект
    return *this;
}
