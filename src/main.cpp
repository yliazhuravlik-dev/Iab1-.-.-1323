#include "Keeper.h"                    // Подключаем заголовочный файл класса Keeper
#include <iostream>                    // Подключаем библиотеку для ввода-вывода
#include <string>                      // Подключаем библиотеку для работы со строками
#include "Keeper.h"                    // Дублирующее включение (можно удалить)

// Функция для отображения главного меню
void displayMenu() {
    std::cout << "\n=== Character Management System ===" << std::endl;  // Заголовок системы
    std::cout << "1. Add Hero" << std::endl;                           // Опция 1 - добавить героя
    std::cout << "2. Add Villain" << std::endl;                        // Опция 2 - добавить злодея
    std::cout << "3. Add Monster" << std::endl;                        // Опция 3 - добавить монстра
    std::cout << "4. Display All Characters" << std::endl;             // Опция 4 - показать всех персонажей
    std::cout << "5. Edit Character" << std::endl;                     // Опция 5 - редактировать персонажа
    std::cout << "6. Remove Character" << std::endl;                   // Опция 6 - удалить персонажа
    std::cout << "7. Save to File" << std::endl;                       // Опция 7 - сохранить в файл
    std::cout << "8. Load from File" << std::endl;                     // Опция 8 - загрузить из файла
    std::cout << "9. Exit" << std::endl;                               // Опция 9 - выход из программы
    std::cout << "Choose an option: ";                                 // Приглашение к выбору опции
}

// Функция для добавления героя в систему
void addHero(Keeper& keeper) {                    // Принимает ссылку на объект Keeper
    std::string name, weapon;                     // Объявление переменных для имени и оружия
    int skillsCount;                              // Переменная для количества навыков

    std::cout << "Enter hero name: ";             // Запрос имени героя
    std::getline(std::cin, name);                 // Чтение всей строки с именем

    std::cout << "Enter weapon type: ";           // Запрос типа оружия
    std::getline(std::cin, weapon);               // Чтение типа оружия

    std::cout << "Enter number of skills: ";      // Запрос количества навыков
    std::cin >> skillsCount;                      // Чтение числа навыков
    std::cin.ignore();                            // Очистка буфера после чтения числа

    // Динамическое выделение массива для навыков
    std::string* skills = new std::string[skillsCount];
    for (int i = 0; i < skillsCount; i++) {       // Цикл для ввода всех навыков
        std::cout << "Enter skill " << (i + 1) << ": ";  // Запрос навыка с номером
        std::getline(std::cin, skills[i]);        // Чтение навыка
    }

    keeper.add(new Hero(name, weapon, skills, skillsCount));  // Создание и добавление героя
    delete[] skills;                              // Освобождение памяти массива навыков
    std::cout << "Hero added successfully!" << std::endl;  // Сообщение об успешном добавлении
}

// Функция для добавления злодея в систему
void addVillain(Keeper& keeper) {                 // Принимает ссылку на объект Keeper
    std::string name, weapon, crime, location;    // Переменные для характеристик злодея
    int skillsCount;                              // Переменная для количества навыков

    std::cout << "Enter villain name: ";          // Запрос имени злодея
    std::getline(std::cin, name);                 // Чтение имени

    std::cout << "Enter weapon type: ";           // Запрос типа оружия
    std::getline(std::cin, weapon);               // Чтение оружия

    std::cout << "Enter crime: ";                 // Запрос преступления
    std::getline(std::cin, crime);                // Чтение преступления

    std::cout << "Enter location: ";              // Запрос местоположения
    std::getline(std::cin, location);             // Чтение местоположения

    std::cout << "Enter number of skills: ";      // Запрос количества навыков
    std::cin >> skillsCount;                      // Чтение числа навыков
    std::cin.ignore();                            // Очистка буфера

    // Динамическое выделение массива для навыков
    std::string* skills = new std::string[skillsCount];
    for (int i = 0; i < skillsCount; i++) {       // Цикл для ввода навыков
        std::cout << "Enter skill " << (i + 1) << ": ";  // Запрос навыка
        std::getline(std::cin, skills[i]);        // Чтение навыка
    }

    keeper.add(new Villain(name, weapon, crime, location, skills, skillsCount));  // Добавление злодея
    delete[] skills;                              // Освобождение памяти
    std::cout << "Villain added successfully!" << std::endl;  // Сообщение об успехе
}

// Функция для добавления монстра в систему
void addMonster(Keeper& keeper) {                 // Принимает ссылку на объект Keeper
    std::string name, appearance;                 // Переменные для имени и внешности

    std::cout << "Enter monster name: ";          // Запрос имени монстра
    std::getline(std::cin, name);                 // Чтение имени

    std::cout << "Enter appearance description: "; // Запрос описания внешности
    std::getline(std::cin, appearance);           // Чтение описания

    keeper.add(new Monster(name, appearance));    // Создание и добавление монстра
    std::cout << "Monster added successfully!" << std::endl;  // Сообщение об успехе
}

// Главная функция программы
int main() {
    Keeper keeper;                                // Создание объекта Keeper для управления данными
    int choice;                                   // Переменная для выбора пользователя

    do {                                          // Начало цикла меню
        try {                                     // Начало блока обработки исключений
            displayMenu();                        // Вывод меню на экран
            std::cin >> choice;                   // Чтение выбора пользователя
            std::cin.ignore();                    // Очистка буфера после чтения числа

            switch (choice) {                     // Оператор выбора по введенному числу
            case 1:                               // Если выбран вариант 1
                addHero(keeper);                  // Вызов функции добавления героя
                break;                            // Выход из case

            case 2:                               // Если выбран вариант 2
                addVillain(keeper);               // Вызов функции добавления злодея
                break;                            // Выход из case

            case 3:                               // Если выбран вариант 3
                addMonster(keeper);               // Вызов функции добавления монстра
                break;                            // Выход из case

            case 4:                               // Если выбран вариант 4
                keeper.displayAll();              // Вызов метода отображения всех персонажей
                break;                            // Выход из case

            case 5: {                             // Если выбран вариант 5 (редактирование)
                if (keeper.getSize() == 0) {      // Проверка на пустую коллекцию
                    std::cout << "No characters to edit." << std::endl;  // Сообщение о пустоте
                    break;                        // Выход из case
                }

                std::cout << "Enter character index to edit (1-" << keeper.getSize() << "): ";  // Запрос индекса
                int index;                        // Переменная для индекса
                std::cin >> index;                // Чтение индекса
                std::cin.ignore();                // Очистка буфера

                if (index < 1 || index > keeper.getSize()) {  // Проверка валидности индекса
                    std::cout << "Invalid index!" << std::endl;  // Сообщение об ошибке
                }
                else {                            // Если индекс корректен
                    keeper.edit(index - 1);       // Вызов метода редактирования (индекс-1 для 0-based)
                    std::cout << "Character edited successfully!" << std::endl;  // Сообщение об успехе
                }
                break;                            // Выход из case
            }

            case 6: {                             // Если выбран вариант 6 (удаление)
                if (keeper.getSize() == 0) {      // Проверка на пустую коллекцию
                    std::cout << "No characters to remove." << std::endl;  // Сообщение о пустоте
                    break;                        // Выход из case
                }

                std::cout << "Enter character index to remove (1-" << keeper.getSize() << "): ";  // Запрос индекса
                int index;                        // Переменная для индекса
                std::cin >> index;                // Чтение индекса
                std::cin.ignore();                // Очистка буфера

                if (index < 1 || index > keeper.getSize()) {  // Проверка валидности индекса
                    std::cout << "Invalid index!" << std::endl;  // Сообщение об ошибке
                }
                else {                            // Если индекс корректен
                    keeper.remove(index - 1);     // Вызов метода удаления
                    std::cout << "Character removed successfully!" << std::endl;  // Сообщение об успехе
                }
                break;                            // Выход из case
            }

            case 7: {                             // Если выбран вариант 7 (сохранение)
                std::string filename;             // Переменная для имени файла
                std::cout << "Enter filename to save: ";  // Запрос имени файла
                std::getline(std::cin, filename); // Чтение имени файла
                keeper.saveToFile(filename);      // Вызов метода сохранения
                break;                            // Выход из case
            }

            case 8: {                             // Если выбран вариант 8 (загрузка)
                std::string filename;             // Переменная для имени файла
                std::cout << "Enter filename to load: ";  // Запрос имени файла
                std::getline(std::cin, filename); // Чтение имени файла
                keeper.loadFromFile(filename);    // Вызов метода загрузки
                break;                            // Выход из case
            }

            case 9:                               // Если выбран вариант 9 (выход)
                std::cout << "Goodbye!" << std::endl;  // Прощальное сообщение
                break;                            // Выход из case

            default:                              // Если введен неверный вариант
                std::cout << "Invalid choice! Please try again." << std::endl;  // Сообщение об ошибке
            }

        }
        catch (const Keeper::Exception& e) {      // Обработка пользовательских исключений Keeper
            std::cout << "Error: " << e.getMessage() << std::endl;  // Вывод сообщения об ошибке
        }
        catch (const std::exception& e) {         // Обработка стандартных исключений
            std::cout << "Unexpected error: " << e.what() << std::endl;  // Вывод неожиданной ошибки
        }

    } while (choice != 9);                        // Условие продолжения цикла (пока не выбран выход)

    return 0;                                     // Успешное завершение программы
}
