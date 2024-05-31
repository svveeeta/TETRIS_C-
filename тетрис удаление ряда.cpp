код на момент видео "удаление ряда"
#include <iostream> 
#include <Windows.h> 
#include <conio.h> 
#include <vector> 

// 1.  
// 2. 
// 3. контроль границ, чтобы фигура не выходила за пределы поля; фиксация фигуры 
// 4. удаление заполненых рядов 
// 5. фиксация фигуры относительно уже установленных (с кодом 2) 
// удаление заполненных рядов, анимация при удалении 


void gotoxy(int x, int y) // переставляет курсор на экране 
{
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

const int WIDTH = 14 + 2; // доп значения для границ 
const int HEIGHT = 12 + 1;

struct Point {
    int x;
    int y;
};

// тк пишем на ООП, создаем классы 

class Figure {
    std::vector <Point> fig;

public:
    void push(int x, int y) {
        Point temp;
        temp.x = x;
        temp.y = y;
        fig.push_back(temp);
    }
    void show() {
        for (int i = 0; i < fig.size(); i++) {
            gotoxy(fig[i].x, fig[i].y);
            std::cout << "*";
        }
    }

    void hide() { // стирание фигуры 
        for (int i = 0; i < fig.size(); i++) {
            gotoxy(fig[i].x, fig[i].y);
            std::cout << " ";
        }
    }

    void moveDown() {
        for (int i = 0; i < fig.size(); i++) {
            fig[i].y++;
        }
    }

    void moveUp() {
        for (int i = 0; i < fig.size(); i++) {
            fig[i].y--;
        }
    }

    void moveLeft() {
        for (int i = 0; i < fig.size(); i++) {
            fig[i].x--;
        }
    }

    void moveRight() {
        for (int i = 0; i < fig.size(); i++) {
            fig[i].x++;
        }
    }

    bool isCollision(const std::vector<std::vector<int>>& vec2d) { // & чтобы не передавать всю копию вектора, только ссылку на него 
        // нам нужно пробежаться по каждой точке, из которых состоит фигура 

        for (int i = 0; i < fig.size(); i++) { // правая граница 
            if (vec2d[fig[i].y][fig[i].x] == 1) // столкновение с границей 
                return true;
            if (vec2d[fig[i].y][fig[i].x] == 2) // столкновение с уже установленной фигурой 
                return true;
        }
        return false;
    }

    void fixed(std::vector<std::vector<int>>& vec2d) {
        // нам нужно пробежаться по каждой точке, из которых состоит фигура 

        for (int i = 0; i < fig.size(); i++) { // правая граница 
            vec2d[fig[i].y][fig[i].x] = 2;
        }
    }

    void spawn() { // 
        // очистим вектор филд и заново поместим новвый 
        fig.clear();

        // через указатель на сам объект, на экземпляр класса вызовем пуш 
        this->push(4, 0);
        this->push(5, 0);
        this->push(4, 1);
        this->push(5, 1);
    }
};

class Game {
    // контейнер, который будет хранить фигуры 
    std::vector <std::vector <int>> field;

public:
    Game() {
    }

    void initVector(std::vector <std::vector<int>>& arr, int width, int height) {
        std::vector <int> temp;
        temp.push_back(1);
        for (int i = 1; i < width - 1; i++) {
            temp.push_back(0);
        }
        temp.push_back(1);

        for (int i = 0; i < height - 1; i++) {
            arr.push_back(temp);
        }

        temp.clear(); // очищаем, тк выше его заполнили 
        for (int i = 1; i < width; i++) {
            temp.push_back(1);
        }
        arr.push_back(temp);
    }


    /*void showZone() {
        for (int i = 0; i < 15; i++) {
            std:: cout << "#" << std::endl;
        }

        for (int i = 0; i < 20; i++) {
            std::cout << "#";
        }

        for (int i = 0; i < 15; i++) {
            gotoxy(19, i);
            std::cout << "#";
        }
    }*/

    void showZone(const std::vector<std::vector<int>>& field) {

        // для отладки 
        for (int i = 0; i < field.size(); i++) {
            gotoxy(24, i);
            std::cout << i << " ";
            if (i < 10)
                std::cout << " ";
            for (int j = 0; j < field[i].size(); ++j) {
                std::cout << field[i][j];
            }
            std::cout << std::endl;
        }

        gotoxy(0, 0);
        for (int i = 0; i < field.size(); i++) {
            for (int j = 0; j < field[i].size(); j++) {
                if (field[i][j] == 1) {
                    std::cout << "#";
                }
                if (field[i][j] == 2) {
                    std::cout << "*";
                }
                else if (field[i][j] == 0) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }

    }

    void deleteLines(int width) {
        std::vector<int> lines; // вектор, который будет хранить номера линий, которые будет требоавться удалить 

        for (int i = field.size() - 2; i >= 0; i--) { // начинаем удалять снизу. -2, тк нам не нужно трогать гарницу 
            int d = 0; // счетчик заполненных ячеек в ряду, для каждой линии нам нужно его обнулять 
            for (int j = 1; j < field[i].size() - 1; j++) { // кажется, стирается правый нижний угол границы 
                if (field[i][j] == 2) {
                    d++;
                }
            }

            if (d == 14) { // удаление ряда 
                lines.push_back(i); // если ряд заполнен, добавляем номер линии в вектор лайнс 
                /*std::cout << "dvjsdkvfd";
                _getch();*/

            }
        }
        gotoxy(0, 25);
        for (int i = 0; i < lines.size(); i++) {
            field.erase(field.begin() + lines[i]); // надо сделать указатель (итератор) на тот элемент,к оторый мы дропаем 
            //std::cout << lines[i] << " "; 
        }

        //showZone(field); 
        //_getch(); 

        std::vector <int> temp;
        // формируются 2 границы 
        temp.push_back(1); // первая 
        for (int i = 1; i < width - 1; i++) { // середина 
            temp.push_back(0);
        }
        temp.push_back(1); // последняя, заполненная нулями 

        for (int i = 0; i < lines.size(); i++) {
            field.insert(field.begin(), temp);
        }
    }

    int run() {

        initVector(field, WIDTH, HEIGHT);
        showZone(field);

        Figure fig;
        fig.spawn();
        /*fig.push(4, 0);
        fig.push(5, 0);
        fig.push(4, 1);
        fig.push(5, 1);*/

        int ch = 0;
        int i = 0;
        int x = 5, y = 5;

        while (true) {

            while (!_kbhit()) { // функция, которая определяет, нажата ли клавиша, то есть цикл "пока клавиша не нажата" 
                /*gotoxy(x, y);
                std::cout << i % 10;
                i++;*/
                fig.hide();
                fig.moveDown();
                if (fig.isCollision(field)) { // если фигура столкнулась 
                    fig.moveUp();
                    fig.fixed(field);
                    deleteLines(WIDTH);
                    showZone(field); // заново прорисовываем поле, после того, как зафиксировали фигуру  
                    fig.spawn(); // генерация новой фигуры 
                }

                fig.show();
                Sleep(200); // чтобы не так быстро падал   

            }
            ch = _getch();

            // нажатие клавиш, вывод их числового кода 
            /*if (ch == 224) {
                ch = _getch();
                gotoxy(20, 20);
                std::cout << ch;
            }*/

            // обработка нажатых клавиш 
            switch (ch) {  // для изменения координат 
            case 77: // код стрелки вправо 
                fig.hide();
                fig.moveRight();

                if (fig.isCollision(field)) { // если фигура столкнулась 
                    fig.moveLeft();
                }
                break;
            case 80: // код стрелки вниз 
                fig.hide();
                fig.moveDown();
                break;
            case 75: // код стрелки влево 
                fig.hide();
                fig.moveLeft();

                if (fig.isCollision(field)) { // если фигура столкнулась 
                    fig.moveRight();
                }

                break;
                //72; // код срелки вверх (не нужно в тетрисе) 

            }
        }

        return 0;
    }
};


int main()
{
    Game game;
    game.run(); //запуск игры 
    //game.initVector(field); 

    std::vector <std::vector <int>> field;

    game.showZone(field);

    //system("pause"); 
    _getch(); // _ позволяет безопасно вызвать данный метод 
}