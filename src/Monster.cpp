#include "Monster.h"                    // Подключаем заголовочный файл класса Monster
#include <iostream>                     // Подключаем библиотеку для ввода-вывода

Monster::Monster() : Base(), appearance("Unknown") { // Конструктор по умолчанию, инициализирует базовый класс и appearance
    std::cout << "Monster default constructor called for: " << name << std::endl; // Вывод отладочной информации
}

Monster::Monster(const std::string& name, const std::string& appearance) // Конструктор с параметрами
    : Base(name), appearance(appearance) { // Инициализация базового класса и поля appearance
    std::cout << "Monster parameterized constructor called for: " << name << std::endl; // Вывод отладочной информации
}

Monster::Monster(const Monster& other) : Base(other), appearance(other.appearance) { // Конструктор копирования
    std::cout << "Monster copy constructor called for: " << name << std::endl; // Вывод отладочной информации
}

Monster::~Monster() { // Деструктор
    std::cout << "Monster destructor called for: " << name << std::endl; // Вывод отладочной информации
}

Monster& Monster::operator=(const Monster& other) { // Перегрузка оператора присваивания
    if (this != &other) { // Проверка на самоприсваивание (a = a)
        Base::operator=(other); // Вызов оператора присваивания базового класса
        appearance = other.appearance; // Копирование поля appearance
    }
    return *this; // Возврат ссылки на текущий объект
}

void Monster::display() const { // Метод для вывода информации о монстре
    std::cout << "=== Monster ===" << std::endl; // Заголовок вывода
    std::cout << "Name: " << name << std::endl; // Вывод имени
    std::cout << "Appearance: " << appearance << std::endl; // Вывод описания внешнего вида
}

void Monster::edit() { // Метод для редактирования данных монстра
    std::cout << "Editing Monster: " << name << std::endl; // Сообщение о начале редактирования
    std::cout << "Enter new name: "; // Запрос нового имени
    std::getline(std::cin, name); // Чтение новой строки имени

    std::cout << "Enter appearance description: "; // Запрос нового описания внешнего вида
    std::getline(std::cin, appearance); // Чтение новой строки описания
}

std::string Monster::getType() const { // Метод для получения типа объекта
    return "Monster"; // Возврат строки "Monster"
}

void Monster::saveToFile(std::ofstream& file) const { // Метод для сохранения в файл (бинарный формат)
    // Сохраняем тип объекта
    std::string type = getType(); // Получаем тип объекта
    int typeLength = type.length(); // Получаем длину строки типа
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength)); // Записываем длину типа в файл
    file.write(type.c_str(), typeLength); // Записываем сам тип в файл

    // Сохраняем имя
    int nameLength = name.length(); // Получаем длину имени
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength)); // Записываем длину имени
    file.write(name.c_str(), nameLength); // Записываем само имя

    // Сохраняем внешний вид
    int appearanceLength = appearance.length(); // Получаем длину описания внешнего вида
    file.write(reinterpret_cast<const char*>(&appearanceLength), sizeof(appearanceLength)); // Записываем длину описания
    file.write(appearance.c_str(), appearanceLength); // Записываем само описание
}

void Monster::loadFromFile(std::ifstream& file) { // Метод для загрузки из файла (бинарный формат)
    // Загружаем имя
    int nameLength; // Переменная для хранения длины имени
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)); // Читаем длину имени из файла
    char* nameBuffer = new char[nameLength + 1]; // Выделяем память для буфера имени
    file.read(nameBuffer, nameLength); // Читаем имя из файла в буфер
    nameBuffer[nameLength] = '\0'; // Добавляем нулевой терминатор
    name = nameBuffer; // Присваиваем имя из буфера
    delete[] nameBuffer; // Освобождаем память буфера

    // Загружаем внешний вид
    int appearanceLength; // Переменная для хранения длины описания
    file.read(reinterpret_cast<char*>(&appearanceLength), sizeof(appearanceLength)); // Читаем длину описания
    char* appearanceBuffer = new char[appearanceLength + 1]; // Выделяем память для буфера описания
    file.read(appearanceBuffer, appearanceLength); // Читаем описание из файла в буфер
    appearanceBuffer[appearanceLength] = '\0'; // Добавляем нулевой терминатор
    appearance = appearanceBuffer; // Присваиваем описание из буфера
    delete[] appearanceBuffer; // Освобождаем память буфера
}

std::string Monster::getAppearance() const { // Get-метод для получения описания внешнего вида
    return appearance; // Возврат значения поля appearance
}

void Monster::setAppearance(const std::string& appearance) { // Set-метод для установки описания внешнего вида
    this->appearance = appearance; // Установка нового значения appearance
}
