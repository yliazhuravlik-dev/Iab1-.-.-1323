// Подключаем заголовочный файл класса Monster
#include "Monster.h"

// Подключаем библиотеку для работы с вводом-выводом
#include <iostream>

// Конструктор по умолчанию: инициализирует поля значениями по умолчанию
Monster::Monster() : name("Unknown Monster"), appearance("Terrifying appearance") {
    // Вывод отладочной информации в консоль
    std::cout << "Monster default constructor for " << name << std::endl;
}

// Конструктор с параметрами: принимает имя и описание внешнего вида для инициализации
Monster::Monster(const std::string& name, const std::string& appearance)
    : name(name), appearance(appearance) {
    // Список инициализации устанавливает значения полей
    std::cout << "Monster parametrized constructor for " << name << std::endl;
}

// Конструктор копирования: создает глубокую копию объекта other
Monster::Monster(const Monster& other)
    : name(other.name), appearance(other.appearance) {
    // Копируем все поля из other в новый объект
    std::cout << "Monster copy constructor for " << name << std::endl;
}

// Деструктор: автоматически вызывается при удалении объекта
Monster::~Monster() {
    // Вывод информации о вызове деструктора
    std::cout << "Monster destructor for " << name << std::endl;
}

// Set-метод для установки имени
void Monster::setName(const std::string& name) {
    // this->name обращается к полю класса (чтобы отличить от параметра)
    this->name = name;
}

// Get-метод для получения имени
std::string Monster::getName() const {
    // Возвращаем копию строки name
    return name;
}

// Set-метод для установки описания внешнего вида
void Monster::setAppearance(const std::string& appearance) {
    this->appearance = appearance;
}

// Get-метод для получения описания внешнего вида
std::string Monster::getAppearance() const {
    return appearance;
}

// Метод для вывода информации о монстре
void Monster::print() const {
    // Выводим информацию о монстре в форматированном виде
    std::cout << "Monster: " << name << std::endl;
    std::cout << "Appearance: " << appearance << std::endl;
    std::cout << "-------------------" << std::endl;
}

// Метод для сохранения данных в файл
void Monster::saveToFile(std::ofstream& out) const {
    // Записываем идентификатор типа для последующей загрузки
    out << "Monster\n";
    // Записываем наименование монстра
    out << name << "\n";
    // Записываем описание внешнего вида
    out << appearance << "\n";
}

// Метод для загрузки данных из файла
void Monster::loadFromFile(std::ifstream& in) {
    // Считываем наименование монстра
    std::getline(in, name);
    // Считываем описание внешнего вида
    std::getline(in, appearance);
}

// Перегрузка оператора присваивания
Monster& Monster::operator=(const Monster& other) {
    // Проверка на самоприсваивание (a = a)
    if (this != &other) {
        // Копируем все поля из other
        name = other.name;
        appearance = other.appearance;
    }
    // Возвращаем ссылку на текущий объект
    return *this;
}
