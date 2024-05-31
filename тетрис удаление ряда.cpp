��� �� ������ ����� "�������� ����"
#include <iostream> 
#include <Windows.h> 
#include <conio.h> 
#include <vector> 

// 1.  
// 2. 
// 3. �������� ������, ����� ������ �� �������� �� ������� ����; �������� ������ 
// 4. �������� ���������� ����� 
// 5. �������� ������ ������������ ��� ������������� (� ����� 2) 
// �������� ����������� �����, �������� ��� �������� 


void gotoxy(int x, int y) // ������������ ������ �� ������ 
{
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

const int WIDTH = 14 + 2; // ��� �������� ��� ������ 
const int HEIGHT = 12 + 1;

struct Point {
    int x;
    int y;
};

// �� ����� �� ���, ������� ������ 

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

    void hide() { // �������� ������ 
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

    bool isCollision(const std::vector<std::vector<int>>& vec2d) { // & ����� �� ���������� ��� ����� �������, ������ ������ �� ���� 
        // ��� ����� ����������� �� ������ �����, �� ������� ������� ������ 

        for (int i = 0; i < fig.size(); i++) { // ������ ������� 
            if (vec2d[fig[i].y][fig[i].x] == 1) // ������������ � �������� 
                return true;
            if (vec2d[fig[i].y][fig[i].x] == 2) // ������������ � ��� ������������� ������� 
                return true;
        }
        return false;
    }

    void fixed(std::vector<std::vector<int>>& vec2d) {
        // ��� ����� ����������� �� ������ �����, �� ������� ������� ������ 

        for (int i = 0; i < fig.size(); i++) { // ������ ������� 
            vec2d[fig[i].y][fig[i].x] = 2;
        }
    }

    void spawn() { // 
        // ������� ������ ���� � ������ �������� ������ 
        fig.clear();

        // ����� ��������� �� ��� ������, �� ��������� ������ ������� ��� 
        this->push(4, 0);
        this->push(5, 0);
        this->push(4, 1);
        this->push(5, 1);
    }
};

class Game {
    // ���������, ������� ����� ������� ������ 
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

        temp.clear(); // �������, �� ���� ��� ��������� 
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

        // ��� ������� 
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
        std::vector<int> lines; // ������, ������� ����� ������� ������ �����, ������� ����� ����������� ������� 

        for (int i = field.size() - 2; i >= 0; i--) { // �������� ������� �����. -2, �� ��� �� ����� ������� ������� 
            int d = 0; // ������� ����������� ����� � ����, ��� ������ ����� ��� ����� ��� �������� 
            for (int j = 1; j < field[i].size() - 1; j++) { // �������, ��������� ������ ������ ���� ������� 
                if (field[i][j] == 2) {
                    d++;
                }
            }

            if (d == 14) { // �������� ���� 
                lines.push_back(i); // ���� ��� ��������, ��������� ����� ����� � ������ ����� 
                /*std::cout << "dvjsdkvfd";
                _getch();*/

            }
        }
        gotoxy(0, 25);
        for (int i = 0; i < lines.size(); i++) {
            field.erase(field.begin() + lines[i]); // ���� ������� ��������� (��������) �� ��� �������,� ������ �� ������� 
            //std::cout << lines[i] << " "; 
        }

        //showZone(field); 
        //_getch(); 

        std::vector <int> temp;
        // ����������� 2 ������� 
        temp.push_back(1); // ������ 
        for (int i = 1; i < width - 1; i++) { // �������� 
            temp.push_back(0);
        }
        temp.push_back(1); // ���������, ����������� ������ 

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

            while (!_kbhit()) { // �������, ������� ����������, ������ �� �������, �� ���� ���� "���� ������� �� ������" 
                /*gotoxy(x, y);
                std::cout << i % 10;
                i++;*/
                fig.hide();
                fig.moveDown();
                if (fig.isCollision(field)) { // ���� ������ ����������� 
                    fig.moveUp();
                    fig.fixed(field);
                    deleteLines(WIDTH);
                    showZone(field); // ������ ������������� ����, ����� ����, ��� ������������� ������  
                    fig.spawn(); // ��������� ����� ������ 
                }

                fig.show();
                Sleep(200); // ����� �� ��� ������ �����   

            }
            ch = _getch();

            // ������� ������, ����� �� ��������� ���� 
            /*if (ch == 224) {
                ch = _getch();
                gotoxy(20, 20);
                std::cout << ch;
            }*/

            // ��������� ������� ������ 
            switch (ch) {  // ��� ��������� ��������� 
            case 77: // ��� ������� ������ 
                fig.hide();
                fig.moveRight();

                if (fig.isCollision(field)) { // ���� ������ ����������� 
                    fig.moveLeft();
                }
                break;
            case 80: // ��� ������� ���� 
                fig.hide();
                fig.moveDown();
                break;
            case 75: // ��� ������� ����� 
                fig.hide();
                fig.moveLeft();

                if (fig.isCollision(field)) { // ���� ������ ����������� 
                    fig.moveRight();
                }

                break;
                //72; // ��� ������ ����� (�� ����� � �������) 

            }
        }

        return 0;
    }
};


int main()
{
    Game game;
    game.run(); //������ ���� 
    //game.initVector(field); 

    std::vector <std::vector <int>> field;

    game.showZone(field);

    //system("pause"); 
    _getch(); // _ ��������� ��������� ������� ������ ����� 
}