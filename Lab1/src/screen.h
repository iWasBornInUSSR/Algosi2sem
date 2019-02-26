//
// Created by picknick on 06.02.19.
//

#ifndef LAB1_SCREEN_H
#define LAB1_SCREEN_H

#include <iostream>

    const int XMAX=100; //Размер экрана
    const int YMAX=50;
    class point {	//Точка на экране
    public:
        int x, y;
        explicit point(int a = 0, int b = 0) : x(a), y(b){  }
        friend std::ostream& operator << (std::ostream& stream, const point& point1) {
            return stream << "(" << point1.x << "," << point1.y << ")";
        }
    };
// Набор утилит для работы с экраном
    void put_point(int a, int b); // Вывод точки (2 варианта)
    void put_point(point p) { put_point(p.x, p.y); } //
    void put_line(int, int, int, int); // Вывод линии (2 варианта)
    void put_line(point a, point b)
    { put_line(a.x, a.y, b.x, b.y); }
    extern void screen_init( );	// Создание экрана
    extern void screen_destroy( );	// Удаление экрана
    extern void screen_refresh( );	// Обновление
    extern void screen_clear( );	// Очистка
//————————————————————————————————


#endif //LAB1_SCREEN_H
