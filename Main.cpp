﻿/*
 * Разработайте консольное приложение для выполнения следующих задач.
 *
 * Задача 1.
 * Сведения о каждом автобусе содержат: регистрационный номер автобуса, фамилию
 * и инициалы водителя, назначенный номер маршрута, фактический номер маршрута.
 * Нахождение в парке – особый маршрут с номером «0», в состав номера маршрута
 * входят как цифры, так и буквы, например – «42», «42а», «32в». Приложение
 * должно обеспечивать выбор с помощью меню и выполнение одной из следующих
 * функций:
 *     • начальное формирование коллекции данных обо всех автобусах,
 *       копирование этой коллекции в коллекции автобусов, находящихся
 *       в парке, находящихся на маршруте;
 *     • имитация выезда автобуса из парка: вводится номер автобуса; удаляются
 *       данные об этом автобусе из коллекции автобусов, находящихся в парке,
 *       и записывает эти данные в коллекцию автобусов, находящихся
 *       на маршрутах;
 *     • имитация въезда автобуса в парк: вводится номер автобуса; удаляются
 *       данные об этом автобусе из коллекции автобусов, находящихся на маршрутах,
 *       и записываются эти данные в коллекцию автобусов, находящихся в парке;
 *     • вывод сведений об автобусах, находящихся в парке, и об автобусах,
 *       находящихся на маршрутах, упорядоченных по регистрационным номерам
 *       автобусов;
 *     • вывод сведений об автобусах, находящихся в парке, и об автобусах,
 *       находящихся на маршрутах, упорядоченных по номерам маршрутов
 *     • сохранение коллекции всех автобусов в бинарном файле;
 *     • чтение данных обо всех автобусах из бинарного файла в коллекцию. 
 * Хранение всех необходимых коллекций организовать с применением контейнерного
 * класса map, в качестве ключа использовать «регистрационный номер автобуса».
 *
 * Задача 2.
 * Напишите решения задач из сборника Абрамяна М.Э., тип данных, который
 * обрабатывается в задачах – int, коллекции заполнять случайными числами: 
 *     • Дан непустой стек (класс stack). Создать два новых стека, переместив
 *       в первый из них все элементы исходного стека с положительными
 *       значениями, а во второй — с отрицательными (элементы в новых стеках
 *       будут располагаться в порядке, обратном исходному; один из этих стеков
 *       может оказаться пустым). Вывести стеки до и после обработки.
 *     • Даны две непустые очереди (класс queue). Перемещать элементы из начала
 *       первой очереди в конец второй, пока значение начального элемента
 *       первой очереди не станет равным 0 (если первая очередь не содержит
 *       нулевых элементов, то переместить из первой очереди во вторую все
 *       элементы). Вывести очереди до и после обработки. 
 *     • Дан двусвязный список (класс list), содержащий не менее двенадцати
 *       элементов. Вывести этот список. Сохранить его в бинарном файле.
 *       Продублировать в списке элементы, значение которых попадает в заданный
 *       с клавиатуры диапазон значений (новые элементы добавлять перед
 *       существующими элементами) и вывести преобразованный список.
 *       Восстановить список из бинарного файла. При помощи set определите все
 *       различные значения в списке, количество таких значений.
 * 
 */


#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"
#include "Palette.h"


int main()
{
	// настройка вывода в консоль
	init(L"Практика");
    ostringstream oss;

	// коды команд
    enum Commands: int {
    	CMD_ONE = 1001, // Начальное формирование коллекций автобусов
    	CMD_TWO,        // Имитация выезда автобуса из парка на маршрут
    	CMD_THREE,      // Имитация возврата автобуса с маршрута в парк
    	CMD_FOUR,       // Вывод сведений об автобусах, упорядоченных по рег. номерам 
    	CMD_FIVE,       // Вывод сведений об автобусах, упорядоченных по маршрутам 
    	CMD_SIX,        // Cохранение коллекции всех автобусов в бинарном файле 
    	CMD_SEVEN,      // Чтение данных обо всех автобусах из бинарного файла в коллекцию

		CMD_EIGHT,      // Обработка стека stack<int>
		CMD_NINE,       // Обработка очереди queue<int>
		CMD_TEN         // Обработка двусвязного списка list<int>
    	
    };

	// вектор пунктов меню
    vector<MenuItem> items = {
        MenuItem (CMD_ONE, "Начальное формирование коллекций автобусов"),
        MenuItem (CMD_TWO, "Имитация выезда автобуса из парка на маршрут"),
        MenuItem (CMD_THREE, "Имитация возврата автобуса с маршрута в парк"),
        MenuItem (CMD_FOUR, "Вывод сведений об автобусах, упорядоченных по рег. номерам"),
        MenuItem (CMD_FIVE, "Вывод сведений об автобусах, упорядоченных по фактическим маршрутам"),
        MenuItem (CMD_SIX, "Cохранение коллекции всех автобусов в бинарном файле"),
        MenuItem (CMD_SEVEN, "Чтение данных обо всех автобусах из бинарного файла в коллекцию"),

        MenuItem (CMD_EIGHT, "Обработка стека stack<int>"),
        MenuItem (CMD_NINE, "Обработка очереди queue<int>"),
        MenuItem (CMD_TEN, "Обработка двусвязного списка list<int>"),

        MenuItem (Menu::CMD_QUIT, "Выход")
    };

    Menu mainMenu(COORD{ 5, 5 }, items, infoColor, hintColor);

	// Объект класса для обработки по заданию
    App *app = new App();   
    
    while(true) {
        try {
            cout << color(mainColor) << cls;
            showNavBarMessage(hintColor, "  Работа с STL контейнерами объектов - последовательными и ассоциативными контейнерами");

            int cmd = mainMenu.navigate();

            cout << color(mainColor) << cls;
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
            // Начальное формирование коллекций автобусов
            case CMD_ONE:
                app->demoInitialize();
                break;
            	
            // Имитация выезда автобуса из парка на маршрут
            case CMD_TWO:
                app->demoGoOut();
                break;

            // Имитация возврата автобуса с маршрута в парк
            case CMD_THREE:
                app->demoGoIn();
                break;
            	
            // Вывод сведений об автобусах, упорядоченных по рег. номерам
            case CMD_FOUR:
                app->showOrderdByRegNum();
                break;
            	
            // Вывод сведений об автобусах, упорядоченных по фактическим номерам маршрутов
            case CMD_FIVE:
                app->showOrderdByRoutes();
                break;

            // Cохранение коллекции всех автобусов в бинарном файле
            case CMD_SIX:
                app->demoSaveToBinStream();
                break;

            // Чтение данных обо всех автобусах из бинарного файла в коллекцию
            case CMD_SEVEN:
                app->demoLoadFromBinStream();
                break;

            // Обработка стека stack<int>
            case CMD_EIGHT:
                app->doStack();
                break;

            // Обработка очереди queue<int>
            case CMD_NINE:
                app->doQueue();
                break;

            // Обработка двусвязного списка list<int>
            case CMD_TEN:
                app->doList();
                break;
            } // switch
        }
        catch (exception& ex) {
            // заливка экрана базовым цветом, вывод строки навигации с сообщением
            cout << color(mainColor) << cls;
            showNavBarMessage(hintColor, "  Ошибка в приложении, нажмите любую клавишу для продолжения");

            int width = 72;

            oss.str("");
            oss << endlm(4) << left
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << "    [Ошибка]" << "\n"
                << "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << " " << "\n"
                << endlm(4)
                << right;
            showMessage(oss.str(), errColor, mainColor);
        } // try-catch

        getKey("\tНажмите любую клавишу для продолжения...");
    } // while

    delete app;
    cls();
    return 0;
} // main
