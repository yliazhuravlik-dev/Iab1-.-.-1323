#include "Keeper.h"                    // Подключаем заголовочный файл класса Keeper
#include <iostream>                    // Подключаем библиотеку для ввода-вывода

Keeper::Keeper() : size(0), capacity(10) {  // Конструктор: инициализация размера=0, вместимости=10
    data = new Base * [capacity];            // Выделяем память для массива указателей на Base
    std::cout << "Keeper default constructor called" << std::endl;  // Сообщение о создании объекта
}

Keeper::~Keeper() {                         // Деструктор - освобождает память
    for (int i = 0; i < size; i++) {       // Проходим по всем элементам
        delete data[i];                     // Удаляем каждый объект в массиве
    }
    delete[] data;                          // Удаляем сам массив указателей
    std::cout << "Keeper destructor called" << std::endl;  // Сообщение об удалении объекта
}

void Keeper::resize() {                     // Увеличение вместимости массива
    capacity *= 2;                          // Увеличиваем вместимость в 2 раза
    Base** newData = new Base * [capacity]; // Создаем новый массив большего размера
    for (int i = 0; i < size; i++) {       // Копируем указатели из старого массива
        newData[i] = data[i];               // Переносим указатель на объект
    }
    delete[] data;                          // Удаляем старый массив
    data = newData;                         // Обновляем указатель на новый массив
}

void Keeper::add(Base* item) {              // Добавление нового элемента
    if (size >= capacity) {                 // Если массив заполнен
        resize();                           // Увеличиваем размер массива
    }
    data[size++] = item;                    // Добавляем элемент и увеличиваем счетчик
}

void Keeper::remove(int index) {            // Удаление элемента по индексу
    if (index < 0 || index >= size) {       // Проверка корректности индекса
        throw Exception("Invalid index for removal");  // Исключение при неверном индексе
    }

    delete data[index];                     // Удаляем объект по указанному индексу
    for (int i = index; i < size - 1; i++) { // Сдвигаем элементы влево
        data[i] = data[i + 1];              // Перемещаем указатель на следующий элемент
    }
    size--;                                 // Уменьшаем счетчик элементов
}

void Keeper::displayAll() const {           // Вывод всех элементов
    if (size == 0) {                        // Если коллекция пуста
        std::cout << "No characters in the collection." << std::endl;  // Сообщение о пустой коллекции
        return;                             // Выход из метода
    }

    for (int i = 0; i < size; i++) {       // Проходим по всем элементам
        std::cout << "=== Character " << (i + 1) << " ===" << std::endl;  // Заголовок для элемента
        data[i]->display();                 // Вызываем метод display() для объекта
        std::cout << std::endl;             // Пустая строка между элементами
    }
}

void Keeper::edit(int index) {              // Редактирование элемента по индексу
    if (index < 0 || index >= size) {       // Проверка корректности индекса
        throw Exception("Invalid index for editing");  // Исключение при неверном индексе
    }
    data[index]->edit();                    // Вызываем метод edit() для объекта
}

void Keeper::saveToFile(const std::string& filename) const {  // Сохранение в файл
    std::ofstream file(filename, std::ios::binary);  // Открываем файл в бинарном режиме
    if (!file) {                             // Если файл не открылся
        throw Exception("Cannot open file for writing: " + filename);  // Исключение
    }

    // Сохраняем количество объектов
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));  // Записываем размер коллекции

    // Сохраняем каждый объект
    for (int i = 0; i < size; i++) {       // Проходим по всем элементам
        data[i]->saveToFile(file);          // Сохраняем каждый объект в файл
    }

    file.close();                           // Закрываем файл
    std::cout << "Data saved to file: " << filename << std::endl;  // Сообщение об успешном сохранении
}

void Keeper::loadFromFile(const std::string& filename) {  // Загрузка из файла
    std::ifstream file(filename, std::ios::binary);  // Открываем файл в бинарном режиме
    if (!file) {                             // Если файл не открылся
        throw Exception("Cannot open file for reading: " + filename);  // Исключение
    }

    // Очищаем текущие данные
    for (int i = 0; i < size; i++) {       // Проходим по всем текущим элементам
        delete data[i];                     // Удаляем каждый объект
    }
    size = 0;                               // Сбрасываем счетчик элементов

    // Загружаем количество объектов
    int newSize;                            // Переменная для хранения размера из файла
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));  // Читаем размер коллекции

    // Загружаем каждый объект
    for (int i = 0; i < newSize; i++) {    // Проходим по всем объектам в файле
        // Читаем тип объекта
        int typeLength;                     // Длина строки с типом объекта
        file.read(reinterpret_cast<char*>(&typeLength), sizeof(typeLength));  // Читаем длину типа

        char* typeBuffer = new char[typeLength + 1];  // Выделяем память для строки типа
        file.read(typeBuffer, typeLength);  // Читаем строку типа из файла
        typeBuffer[typeLength] = '\0';      // Добавляем нулевой терминатор
        std::string type(typeBuffer);       // Создаем строку из буфера
        delete[] typeBuffer;                // Освобождаем память буфера

        // Создаем объект соответствующего типа
        Base* newObject = nullptr;          // Указатель на новый объект
        if (type == "Hero") {               // Если тип - Hero
            newObject = new Hero();         // Создаем объект Hero
        }
        else if (type == "Villain") {       // Если тип - Villain
            newObject = new Villain();      // Создаем объект Villain
        }
        else if (type == "Monster") {       // Если тип - Monster
            newObject = new Monster();      // Создаем объект Monster
        }
        else {                              // Если неизвестный тип
            throw Exception("Unknown object type in file: " + type);  // Исключение
        }

        // Загружаем данные объекта
        newObject->loadFromFile(file);      // Загружаем данные в объект
        add(newObject);                     // Добавляем объект в коллекцию
    }

    file.close();                           // Закрываем файл
    std::cout << "Data loaded from file: " << filename << std::endl;  // Сообщение об успешной загрузке
}

int Keeper::getSize() const {               // Получение текущего размера коллекции
    return size;                            // Возвращаем количество элементов
}

Base* Keeper::get(int index) const {        // Получение элемента по индексу
    if (index < 0 || index >= size) {       // Проверка корректности индекса
        throw Exception("Invalid index");   // Исключение при неверном индексе
    }
    return data[index];                     // Возвращаем указатель на объект
}
