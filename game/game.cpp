// game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

struct PERSON
{
    PERSON()                                             // конструктор по умолчанию
    {
        name = "Enemy #";
        health = 1;
        armor = 0;
        damage = 0;
        x = 0;
        y = 0;
        move = 4;
        life = true;
        if (health < 1)                                  // если жизней меньше 1 , то персонаж умер
        {
            life = false;
        }
    }


    std::string name;
    int health;
    int armor;
    int damage;
    int x;
    int y;
    int move;                                            // переменная - передвижение.
    bool life;                                           // жив ли персонаж


    void Get() const
    {
        std::cout << "name: " << name << "\nhealth: " << health << "\narmor:" << armor << "\ndamage: " << damage << "\ncoordinates: " << x << ',' << y << "\nLIFE: " << life << std::endl;
    }
};
void FILLING(char Game_field[][20])                      // Заполнение игрового поля точками(ОБНУЛЕНИЕ КАРТИНКИ) ! очень часто используемая функция
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            Game_field[i][j] = '.';
        }
    }
}

void LOAD_INFO_FIELD(char Game_field[][20], PERSON Player[]) // загрузка информации о нахождении героя и врагов в поле  
{
    Game_field[Player[0].y][Player[0].x] = 'P';          // первая переменная  у вторая х для более привычных координат

    for (int i = 1; i < 6; i++)
    {
        if (Player[i].life)
        {
            Game_field[Player[i].y][Player[i].x] = 'E';     // картинка врагов
        }
    }
};

void DISPLAY_FIELD(char Game_field[][20])               // (КАРТИНКА) вывод игрового поля на экран
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            std::cout << Game_field[i][j];
        }
        std::cout << std::endl;
    }
};

void REPLACEMENT(std::string move_char, PERSON Player[])      // функция перемещения меняет буквы на цифры лдя дальнейшего перемещения
{
    if (move_char == "w")
    {
        Player[6].move = 0;
        return;
    }
    if (move_char == "s")
    {
        Player[6].move = 2;
        return;
    }
    if (move_char == "a")
    {
        Player[6].move = 1;
        return;
    }
    if (move_char == "d")
    {
        Player[6].move = 3;
        return;
    }





    /*switch (move_char)
    {
    case 'w':
        Player[6].move = 0;
        break;
    case 's':
        Player[6].move = 2;
        break;
    case 'a':
        Player[6].move = 1;
        break;
    case 'd':
        Player[6].move = 3;
        break;
    default:
        std::cout << "Неверная команда передвижения";
        break;
    }*/
}

void MOVEMENT(PERSON Player[])  // ПЕРЕДВИЖЕНИЕ ПЕРСОНАЖЕЙ 
{
    for (int i = 0; i < 7; i++)
    {
        switch (Player[i].move)
        {
        case 0:
            Player[i].y--;
            if (Player[i].y < 0)
            {
                Player[i].y = 0;
            }
            Player[i].move = 4;   // ЧЕ НАПИСАЛ?? ЗАЧЕМ ЭТО ?? Я НЕ ПОМНЮ... АА.. чтобы персонаж делал один ход!!!!
            break;

        case 1:
            Player[i].x--;
            if (Player[i].x < 0)
            {
                Player[i].x = 0;
            }
            Player[i].move = 4;
            break;

        case 2:
            Player[i].y++;
            if (Player[i].y > 19)
            {
                Player[i].y = 19;
            }
            Player[i].move = 4;
            break;

        case 3:
            Player[i].x++;
            if (Player[i].x > 19)
            {
                Player[i].x = 19;
            }
            Player[i].move = 4;
            break;
        case 4:                                       // case 4  - если персонаж наткнется на другого и произойдет удар, он должен оставаться на месте. 
            break;
        }
    }


}

void Kartinka(char Game_field[][20], PERSON Player[])
{
    FILLING(Game_field);                            //обнуление картинки
    LOAD_INFO_FIELD(Game_field, Player);            // новые актуальные данные
    DISPLAY_FIELD(Game_field);                      // вывод поля на экран ( показ картинки)
}

void ENEMY_MOVE(PERSON Player[])                    //перемещение врагов
{
    for (int i = 1; i < 6; i++)
    {
        if (Player[i].life)                         // если персонаж жив                            
        {
            Player[6] = Player[i];
            Player[6].move = rand() % 4;
            // сюда вставляем перемещение
            MOVEMENT(Player);                    // передвижение персонажa


            if ((Player[0].x - Player[6].x == 0) && (Player[0].y - Player[6].y == 0))
            {
                Player[0].armor -= Player[6].damage;
                if (Player[0].armor < 0)
                {
                    Player[0].health += Player[0].armor;
                    Player[0].armor = 0;
                    if (Player[0].health < 1)
                    {
                        Player[0].life = false;
                    }
                }
            }
            else
            {
                Player[i] = Player[6];
            }
        }
    }
}

void HERO_DAMAGE(PERSON Player[])
{
    for (int i = 1; i < 6; i++)
    {
        if (Player[i].life)
        {
            if ((Player[6].x - Player[i].x == 0) && (Player[6].y - Player[i].y == 0))    // если герой и враг сблизились, наносится урон
            {
                Player[i].armor -= Player[6].damage;
                if (Player[i].armor < 0)
                {
                    Player[i].health += Player[i].armor;
                    Player[i].armor = 0;
                    if (Player[i].health < 1)
                    {
                        Player[i].life = false;                                          // если жизней меньше 1 , персонаж умирает
                    }
                }
                return;                                                                  // если сближение произошло выходим из функции
            }
        }
    }
    Player[0] = Player[6];                                                           // если персонажи не сблизились, то временная переменная передает герою координаты передвижения, и он ходит
}

//void save(std::string path, PERSON Player[])
//{
//    std::ofstream w_file(path, std::ios::binary | std::ios::out); // запись в бинарный файл
//    if (!w_file.is_open())
//    {
//        std::cerr << "FILE IS NOT OPEN!";
//        return;
//    }
//    for (int i = 0; i < 7; i++)
//    {
//        int len = Player[i].name.length();
//        w_file.write((char*)&len, sizeof(int));
//        w_file.write(Player[i].name.c_str(), len);
//
//        w_file.write((char*)&Player[i].health, sizeof(Player[i].health));
//
//        w_file.write((char*)&Player[i].armor, sizeof(Player[i].armor));
//
//        w_file.write((char*)&Player[i].damage, sizeof(Player[i].damage));
//
//        w_file.write((char*)&Player[i].x, sizeof(Player[i].x));
//
//        w_file.write((char*)&Player[i].y, sizeof(Player[i].y));
//
//        w_file.write((char*)&Player[i].move, sizeof(Player[i].move));
//
//        w_file.write(reinterpret_cast<char*>(&Player[i].life), sizeof(Player[i].life));
//
//    }
//    w_file.close();
//
//}
//void load(std::string path, PERSON Player[])
//{
//    std::ifstream r_file(path, std::ios::binary | std::ios::in);
//    if (!r_file.is_open())
//    {
//        std::cerr << "r_file is NOT OPEN!";
//        return;
//    }
//    for (int i = 0; i < 7; i++)
//    {
//        int len = 0;
//        r_file.read((char*)len, sizeof len);
//        Player[i].name.resize(len);           // в данном случае нужно ли ресайзать name ??
//        r_file.read((char*)Player[i].name.c_str(), len);
//
//        r_file.read((char*)Player[i].health, sizeof(Player[i].health));
//
//        r_file.read((char*)Player[i].armor, sizeof(Player[i].armor));
//
//        r_file.read((char*)Player[i].damage, sizeof(Player[i].damage));
//
//        r_file.read((char*)Player[i].x, sizeof(Player[i].x));
//
//        r_file.read((char*)Player[i].y, sizeof(Player[i].y));
//
//        r_file.read((char*)Player[i].move, sizeof(Player[i].move));
//
//        r_file.read(reinterpret_cast<char*>(&Player[i].life), sizeof(Player[i].life));
//
//    }
//    r_file.close();
//}

int main()
{
    std::string path = " game.bin";

    std::ofstream w_file(path, std::ios::binary | std::ios::out);
    if (!w_file.is_open())
    {
        std::cout << "FILE IS NOT OPEN!";
    }
    w_file.close();

    setlocale(LC_ALL, "RUS");
    srand(time(NULL));                               // для генерации случайных чисел

    PERSON Player[7];                                // массив-хранение  врагов  0 - ГЛАВНЫЙ ГЕРОЙ , 6 - ВРЕМЕННАЯ ФИГУРА   1-5 ВРАГИ

    char Game_field[20][20];                         // игровое поле 20 на 20 для вывода на экран

    std::cout << " Давайте приступим к созданию героя!\n";

    Player[0].x = rand() % 20;
    Player[0].y = rand() % 20;

    std::cout << "Введите имя персонажа: ";
    std::cin >> Player[0].name;

    std::cout << "Введите количество жизней персонажа: ";
    std::cin >> Player[0].health;

    std::cout << " Введите количество брони: ";
    std::cin >> Player[0].armor;

    std::cout << "Введите урон персонажа: ";
    std::cin >> Player[0].damage;

    // создаем  врагов

    for (int i = 1; i < 7; i++)
    {
        Player[i].name += std::to_string(i);
        Player[i].armor = rand() % 51;
        Player[i].health = rand() % 101 + 50;
        Player[i].damage = rand() % 16 + 15;
        Player[i].x = rand() % 20;
        Player[i].y = rand() % 20;
    }
    Kartinka(Game_field, Player);                      // вывод поля на экран ( показ картинки)

   // save(path, Player);                                // сохраняем данные 

    while (Player[0].life && (Player[1].life + Player[2].life + Player[3].life + Player[4].life + Player[5].life))  // игра началась
    {
        std::string move_char ;                                  // символ перемещения
        std::cout << " введи передвижение: ";
        std::cin >> move_char;                           // ввод перемещения героя

        
            Player[6] = Player[0];                           // приравниваем временного персонажа к герою
            REPLACEMENT(move_char, Player);                  // заполняем переменную Player[6].move  REPLACEMENT - замена  (буквы на цифру)
            MOVEMENT(Player);                               // передвижение персонажей
            HERO_DAMAGE(Player);                             // проверка на сближение и нанесение урона

            ENEMY_MOVE(Player);                              //  создаем случайное  перемещение врагов и тут же  передвижение и урон 
            MOVEMENT(Player);                               // передвижение персонажей

            Player[0].Get();
            std::cout << std::endl;
            Player[1].Get();
            std::cout << std::endl;
            Player[2].Get();
            std::cout << std::endl;
            Player[3].Get();
            std::cout << std::endl;
            Player[4].Get();
            std::cout << std::endl;
            Player[5].Get();
            std::cout << std::endl;

            Kartinka(Game_field, Player);

            std::cout << std::endl;
        }
        if (Player[0].life)
        {
            std::cout << "YOU Win!";
        }
        else
        {
            std::cout << "You LOSE!!!";
        }
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
