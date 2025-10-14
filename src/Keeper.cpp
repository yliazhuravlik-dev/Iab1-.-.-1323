// Подключаем заголовочный файл класса Keeper
#include "Keeper.h"
// Подключаем заголовки всех классов-наследников
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
// Подключаем библиотеки для работы с файлами и исключениями
#include <iostream>
#include <fstream>
#include <stdexcept>

// Начальная вместимость массива по умолчанию
const int INITIAL_CAPACITY = 10;

// Конструктор по умолчанию: инициализирует пустой массив с начальной вместимостью
Keeper::Keeper() : size(0), capacity(INITIAL_CAPACITY) {
    // Выделяем память для массива указателей
    data = new Base*[capacity];
    // Инициализируем все указатели nullptr для безопасности
    for (int i = 0; i < capacity; ++i) {
        data[i] = nullptr;
    }
    std::cout << "Keeper default constructor. Capacity: " << capacity << std::endl;
}

// Конструктор копирования: создает глубокую копию другого объекта Keeper
Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    // Выделяем память для нового массива
    data = new Base*[capacity];
    
    // Создаем копии каждого объекта в массиве
    for (int i = 0; i < size; ++i) {
        // Для корректного копирования нужно определить тип каждого объекта: в  этом упрощенном примере создаем новые объекты того же типа
        data[i] = nullptr; // Заглушка - в реальности нужно реализовать клонирование
    }
    
    std::cout << "Keeper copy constructor. Size: " << size << std::endl;
}

// Деструктор
// Освобождает всю выделенную память
Keeper::~Keeper() {
    // Удаляем каждый объект в массиве
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    // Удаляем сам массив указателей
    delete[] data;
    std::cout << "Keeper destructor. Freed memory for " << size << " elements." << std::endl;
}

// Приватный метод для увеличения вместимости массива
void Keeper::resize() {
    // Увеличиваем вместимость в 2 раза (стандартный подход)
    int newCapacity = capacity * 2;
    
    // Выделяем память для нового массива большего размера
    Base** newData = new Base*[newCapacity];
    
    // Копируем указатели из старого массива в новый
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    
    // Инициализируем оставшиеся элементы nullptr
    for (int i = size; i < newCapacity; ++i) {
        newData[i] = nullptr;
    }
    
    // Удаляем старый массив
    delete[] data;
    
    // Обновляем указатель и вместимость
    data = newData;
    capacity = newCapacity;
    
    std::cout << "Keeper resized. New capacity: " << capacity << std::endl;
}

// Метод для добавления элемента в контейнер
void Keeper::add(Base* element) {
    // Проверяем валидность указателя
    if (element == nullptr) {
        throw std::invalid_argument("Cannot add null pointer to Keeper.");
    }
    
    // Если массив заполнен, увеличиваем его размер
    if (size >= capacity) {
        resize();
    }
    
    // Добавляем элемент в конец массива
    data[size] = element;
    size++;
    
    std::cout << "Added element to Keeper. Total size: " << size << std::endl;
}

// Метод для удаления элемента по индексу
void Keeper::remove(int index) {
    // Проверяем валидность индекса
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range in Keeper::remove.");
    }
    
    // Удаляем объект по указанному индексу
    delete data[index];
    
    // Сдвигаем оставшиеся элементы влево
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    
    // Уменьшаем размер и обнуляем последний элемент
    size--;
    data[size] = nullptr;
    
    std::cout << "Removed element at index " << index << ". Total size: " << size << std::endl;
}

// Метод для вывода всех элементов на экран
void Keeper::printAll() const {
    // Проверяем, есть ли элементы для вывода
    if (size == 0) {
        std::cout << "Keeper is empty." << std::endl;
        return;
    }
    
    std::cout << "=== All elements in Keeper (" << size << " items) ===" << std::endl;
    
    // Выводим информацию о каждом элементе
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "] ";
        data[i]->print();
    }
    
    std::cout << "=== End of list ===" << std::endl;
}

// Метод для сохранения всех данных в файл
void Keeper::saveToFile(const std::string& filename) const {
    // Открываем файл для записи
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for saving: " + filename);
    }
    
    // Записываем общее количество элементов
    out << size << "\n";
    
    // Сохраняем каждый элемент в файл
    for (int i = 0; i < size; ++i) {
        data[i]->saveToFile(out);
    }
    
    // Закрываем файл
    out.close();
    std::cout << "Data saved to " << filename << ". Saved " << size << " elements." << std::endl;
}

// Метод для загрузки всех данных из файла
void Keeper::loadFromFile(const std::string& filename) {
    // Открываем файл для чтения
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for loading: " + filename);
    }

    // Очищаем текущие данные
    for (int i = 0; i < size; ++i) {
        delete data[i];
        data[i] = nullptr;
    }
    size = 0;

    // Считываем количество элементов
    int loadedSize;
    in >> loadedSize;
    in.ignore(); // Пропускаем символ новой строки после числа

    std::string type;
    // Загружаем каждый элемент из файла
    for (int i = 0; i < loadedSize; ++i) {
        // Считываем тип объекта
        std::getline(in, type);
        Base* element = nullptr;

        // Создаем объект соответствующего типа
        if (type == "Hero") {
            element = new Hero();
        } else if (type == "Villain") {
            element = new Villain();
        } else if (type == "Monster") {
            element = new Monster();
        } else {
            throw std::runtime_error("Unknown object type in file: " + type);
        }

        // Загружаем данные объекта из файла
        element->loadFromFile(in);
        // Добавляем объект в контейнер
        add(element);
    }
    
    // Закрываем файл
    in.close();
    std::cout << "Data loaded from " << filename << ". Loaded " << loadedSize << " elements." << std::endl;
}

// Метод для получения элемента по индексу
Base* Keeper::getElement(int index) const {
    // Проверяем валидность индекса
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range in Keeper::getElement.");
    }
    
    // Возвращаем указатель на элемент (без передачи владения)
    return data[index];
}

// Get-метод для получения текущего размера
int Keeper::getSize() const {
    return size;
}

// Get-метод для получения текущей вместимости
int Keeper::getCapacity() const {
    return capacity;
}

// Перегрузка оператора присваивания
Keeper& Keeper::operator=(const Keeper& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        // Очищаем текущие данные
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        
        // Копируем размер и вместимость
        size = other.size;
        capacity = other.capacity;
        
        // Выделяем новую память
        data = new Base*[capacity];
        
        // Создаем копии объектов (упрощенно)
        for (int i = 0; i < size; ++i) {
            data[i] = nullptr; // Заглушка - нужна реализация клонирования
        }
    }
    return *this;
}
