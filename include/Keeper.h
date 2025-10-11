#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>

class Keeper {
private:
    Base** data;
    int size;
    int capacity;
    void resize();

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();
    
    void add(Base* element);
    
    void remove(int index);

    void printAll() const;
    
    void saveToFile(const std::string& filename) const;
  
    void loadFromFile(const std::string& filename);
    
    Base* getElement(int index) const;
    
    int getSize() const;
    int getCapacity() const;

    Keeper& operator=(const Keeper& other);
};

#endif
