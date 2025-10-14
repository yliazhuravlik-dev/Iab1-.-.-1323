#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

const int INITIAL_CAPACITY = 10;

Keeper::Keeper() : size(0), capacity(INITIAL_CAPACITY) {
    data = new Base*[capacity];
    for (int i = 0; i < capacity; ++i) {
        data[i] = nullptr;
    }
    std::cout << "Keeper default constructor. Capacity: " << capacity << std::endl;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base*[capacity];
    
    for (int i = 0; i < size; ++i) {
        data[i] = nullptr; // Заглушка - в реальности нужно реализовать клонирование
    }
    
    std::cout << "Keeper copy constructor. Size: " << size << std::endl;
}

Keeper::~Keeper() {
    // Удаляем каждый объект в массиве
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    std::cout << "Keeper destructor. Freed memory for " << size << " elements." << std::endl;
}

void Keeper::resize() {
    int newCapacity = capacity * 2;
    Base** newData = new Base*[newCapacity];
    
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    
    for (int i = size; i < newCapacity; ++i) {
        newData[i] = nullptr;
    }
    
    delete[] data;
  
    data = newData;
    capacity = newCapacity;
    
    std::cout << "Keeper resized. New capacity: " << capacity << std::endl;
}

void Keeper::add(Base* element) {
    if (element == nullptr) {
        throw std::invalid_argument("Cannot add null pointer to Keeper.");
    }
  
    if (size >= capacity) {
        resize();
    }

    data[size] = element;
    size++;
    
    std::cout << "Added element to Keeper. Total size: " << size << std::endl;
}
void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range in Keeper::remove.");
    }
    delete data[index];
    
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
  
    size--;
    data[size] = nullptr;
    
    std::cout << "Removed element at index " << index << ". Total size: " << size << std::endl;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty." << std::endl;
        return;
    }
    
    std::cout << "=== All elements in Keeper (" << size << " items) ===" << std::endl;
    
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "] ";
        data[i]->print();
    }
    
    std::cout << "=== End of list ===" << std::endl;
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for saving: " + filename);
    }
    
    out << size << "\n";
    for (int i = 0; i < size; ++i) {
        data[i]->saveToFile(out);
    }
    
    out.close();
    std::cout << "Data saved to " << filename << ". Saved " << size << " elements." << std::endl;
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for loading: " + filename);
    }

    for (int i = 0; i < size; ++i) {
        delete data[i];
        data[i] = nullptr;
    }
    size = 0;

    int loadedSize;
    in >> loadedSize;
    in.ignore(); // Пропускаем символ новой строки после числа

    std::string type;
    for (int i = 0; i < loadedSize; ++i) {
        // Считываем тип объекта
        std::getline(in, type);
        Base* element = nullptr;
        if (type == "Hero") {
            element = new Hero();
        } else if (type == "Villain") {
            element = new Villain();
        } else if (type == "Monster") {
            element = new Monster();
        } else {
            throw std::runtime_error("Unknown object type in file: " + type);
        }

        element->loadFromFile(in);
        add(element);
    }
    
    in.close();
    std::cout << "Data loaded from " << filename << ". Loaded " << loadedSize << " elements." << std::endl;
}

Base* Keeper::getElement(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range in Keeper::getElement.");
    }
    
    return data[index];
}

int Keeper::getSize() const {
    return size;
}

int Keeper::getCapacity() const {
    return capacity;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        
        size = other.size;
        capacity = other.capacity;
        data = new Base*[capacity];     
        for (int i = 0; i < size; ++i) {
            data[i] = nullptr; // Заглушка - нужна реализация клонирования
        }
    }
    return *this;
}
