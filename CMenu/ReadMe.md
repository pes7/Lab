#CMenu
####Визуализироване меню, которое очень простое в использовании.
##Инструкция по использувании:
#####Рабочие файлы:
######Cmenu.cpp
######Structures.cpp
#####Вставляем код в свой
        #include "CMenu.cpp"
#####Прописать очитку екрана
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#####Задать базовые переменные
        int slots = 0;
        Menu *menu = NULL;
#####Выделить память на меню, цифра 3 - количество пунктов
        menu = CMenu(menu, 3);
#####Создать тело пункта
        //Название пункта
        menu->text[menu->slots].str = "D)Стек";
        //Кнопки нажатия которых связывают с етим пунктом
        menu->binds[menu->slots].binds = "DВ";
        //Указатель на функцию которая привязана к етому пункту
        menu->pointers[menu->slots] = (int)(void*)&stek_menu;
        //Показуем что будет еще один пункт меню
        menu->slots++;
#####Создать тело меню
        //Заголовок меню
        menu->properties.header = "Меню программы:";
        //Нужная хрень, непомню для чего, лучше держать на 0
        menu->properties.height = 0;
        //Координаты меню
        menu->properties.coords.x = 7;
        menu->properties.coords.y = 4;
        //Размер меню
        menu->properties.size.height = 14;
        menu->properties.size.width = 30;
        //Бинд кнопок останова меню. Ps: никто не мешает сделать отдельный пункт 
        назад с NULL указателем на функцию, который будет останавливать меню.
        menu->properties.dbreak.binds = "PЗ";
        //Для будущей разработки, а может и выкину его вовсе.
        menu->properties.prioritet = 0;
#####Вызвать функцию создания меню
        SmartChoose(menu);
##Полный пример:
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        
        int slots = 0;
        Menu *menu = NULL;

        menu = CMenu(menu, 3);

        menu->text[menu->slots].str = "D)Стек";
        menu->binds[menu->slots].binds = "DВ";
        menu->pointers[menu->slots] = (int)(void*)&stek_menu;
        menu->slots++;

        menu->text[menu->slots].str = "F)Дек";
        menu->binds[menu->slots].binds = "FА";
        menu->pointers[menu->slots] = (int)(void*)&dek_menu;
        menu->slots++;

        menu->text[menu->slots].str = "G)Лист";
        menu->binds[menu->slots].binds = "GП";
        menu->pointers[menu->slots] = (int)(void*)&sap;

        menu->properties.header = "Меню программы:";
        menu->properties.height = 0;
        menu->properties.coords.x = 7;
        menu->properties.coords.y = 4;
        menu->properties.size.height = 14;
        menu->properties.size.width = 30;
        menu->properties.dbreak.binds = "PЗ";
        menu->properties.prioritet = 0;

        SmartChoose(menu);
#####Так же полный рабочий пример находиться в нутри репрозитория.
##Пользуйтесь на здоровье, и не забывайте указывать автора.
