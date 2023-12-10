// game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <string>


struct PERSON
{
    PERSON()                   // конструктор по умолчанию
    {
        name = "Enemy #";
        health = 0;
        armor = 0;
        damage = 0;
        x = 0;
        y = 0;
    }
    

    std::string name;
    int health;
    int armor;
    int damage;
    int x;
    int y;
    int move;                     // переменная - передвижение.

    void Get()
    {
        std::cout << "name: " << name << "\nhealth: " << health << "\narmor:" << armor << "\ndamage: " << damage << "\ncoordinates: " << x << ',' << y << std::endl;
    }
};
void FILLING(char Game_field[][20])            // Заполнение игрового поля точками(ОБНУЛЕНИЕ КАРТИНКИ) ! очень часто используемая функция
{
    for (int i = 0; i < 20; ++i)          
    {
        for (int j = 0; j < 20; ++j)
        {
            Game_field[i][j] = '.';
        }
    }
}

void LOAD_INFO_FIELD(char Game_field[][20],PERSON hero, PERSON  enemy)     // загрузка информации о нахождении героя и врагов в поле  
{
    Game_field[hero.y][hero.x] = 'P';                // первая переменная  у вторая х для более привычных координат
    Game_field[enemy.y][enemy.x] = 'E';
};

void DISPLAY_FIELD(char Game_field[][20])            // (КАРТИНКА) вывод игрового поля на экран
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            std::cout << Game_field[i][j] ;
        }
        std::cout << std::endl;
    }
};

void REPLACEMENT(char move_char, int& dvijenie)                            // функция перемещения меняет буквы на цифры лдя дальнейшего перемещения
{
    switch (move_char)
    {
    case 'u':
        dvijenie = 0;
        break;
    case 'd':
        dvijenie = 2;
        break;
    case 'l':
        dvijenie = 1;
        break;
    case 'r':
        dvijenie = 3;
        break;
    default:
        std::cout << "Неверная команда передвижения";
        break;
    }
}

void MOVEMENT(int dvijenie, char Game_field[][20],PERSON& hero,PERSON enemy)  // это пока тестовая версия.. возможно враги и не понадобятся сюда передавать.. 
{
    switch (dvijenie)
    {
    case 0:
        hero.y--;
        if (hero.y < 0)
        {
            hero.y = 0;
        }
        FILLING(Game_field);                               //обнуление картинки
        LOAD_INFO_FIELD(Game_field, hero, enemy);        // новые актуальные данные
        break; 

    case 1:
        hero.x--;
        if (hero.x < 0)
        {
            hero.x = 0;
        }
        FILLING(Game_field);
        LOAD_INFO_FIELD(Game_field, hero, enemy);
        break;

    case 2:
        hero.y++;
        if (hero.y > 19)
        {
            hero.y = 19;
        }
        FILLING(Game_field);
        LOAD_INFO_FIELD(Game_field, hero, enemy);
        break;

    case 3:
        hero.x++;
        if (hero.x > 19)
        {
            hero.x = 19;
        }
        FILLING(Game_field);
        LOAD_INFO_FIELD(Game_field, hero, enemy);
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));        // для генерации случайных чисел

    PERSON Enemies[5];        // массив-хранение  врагов
    PERSON hero;              // персонаж игрока
    char Game_field[20][20];  // игровое поле 20 на 20 для вывода на экран
    int dvijenie;             // внутренняя переменная для движения
    
    FILLING(Game_field);      // заполнение игрового поля
    
    
    // создам одного врага
    PERSON enemy;
    enemy.name += std::to_string(1);
    enemy.armor = rand() % 51;
    enemy.health = rand() % 101 + 50;
    enemy.damage = rand() % 16 + 15;
    enemy.x = rand() % 20;
    enemy.y = rand() % 20;

    std::cout << " Давайте приступим к созданию героя!\n";

    hero.x = rand() % 20;
    hero.y = rand() % 20;

    LOAD_INFO_FIELD(Game_field, hero, enemy);          //загрузка координат героя в карту

   /* std::cout << "Введите имя персонажа: ";
    std::cin >> hero.name;

    std::cout << "Введите количество жизней персонажа: ";
    std::cin >> hero.health;

    std::cout << " Введите количество брони: ";
    std::cin >> hero.armor;

    std::cout << "Введите урон персонажа: ";
    std::cin >> hero.damage;*/
    enemy.Get();
    hero.Get();                     // тестовый вывод персонажа
    DISPLAY_FIELD(Game_field);    // вывод поля на экран

    

    char move_char;                                // символ перемещения
    std::cout << " введи передвижение: ";
    std::cin >> move_char;

    REPLACEMENT(move_char,dvijenie);                   // заполняем переменную dvijenie  REPLACEMENT - замена  (буквы на цифру)

    MOVEMENT(dvijenie, Game_field, hero, enemy);

    //std::cout << dvijenie;         // тестовый вывод цифры движения

    hero.Get();                      // тестовый вывод персонажа
    

    DISPLAY_FIELD(Game_field);    // вывод поля на экран
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
