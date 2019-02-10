//
// Created by picknick on 06.02.19.
//

#ifndef LAB1_SHAPE_H
#define LAB1_SHAPE_H

#include <iostream>
#include "screen.h"

//======== Файл shape.h -- библиотека фигур =========
//==1. Поддержка экрана в форме матрицы символов ==
char screen[YMAX][XMAX];
enum color {
    black = '*', white = '.'
};

void screen_init() {
    for (auto y = 0; y < YMAX; ++y)
        for (auto &x : screen[y])
            x = white;
}

void screen_destroy() {
    for (auto y = 0; y < YMAX; ++y)
        for (auto &x : screen[y])
            x = black;
}

bool on_screen(int a, int b) // проверка попадания на экран
{ return 0 <= a && a < XMAX && 0 <= b && b < YMAX; }

void put_point(int a, int b) { if (on_screen(a, b)) screen[b][a] = black; }

void put_line(int x0, int y0, int x1, int y1)
/*
Рисование отрезка прямой от (x0,y0) до (x1,y1).
Уравнение прямой: b(x-x0) + a(y-y0) = 0.
Минимизируется величина abs(eps),
где eps = 2*(b(x-x0)) + a(y-y0) (алгоритм Брезенхэма для прямой).
*/
{
    int dx = 1;
    int a = x1 - x0;
    if (a < 0) dx = -1, a = -a;
    int dy = 1;
    int b = y1 - y0;
    if (b < 0) dy = -1, b = -b;
    int two_a = 2 * a;
    int two_b = 2 * b;
    int xcrit = -b + two_a;
    int eps = 0;

    for (;;) { //Формирование прямой линии по точкам
        put_point(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        if (eps <= xcrit) x0 += dx, eps += two_b;
        if (eps >= a || a < b) y0 += dy, eps -= two_a;
    }
}

void screen_clear() { screen_init(); } //Очистка экрана

void screen_refresh() // Обновление экрана
{
    for (int y = YMAX - 1; 0 <= y; --y) { // с верхней строки до нижней
        for (auto x : screen[y])    // от левого столбца до правого
            std::cout << x;
        std::cout << '\n';
    }
}

struct shape { // Виртуальный базовый класс "фигура"
    static shape *list;    // Начало списка фигур (одно на все фигуры!)
    shape *next;

    shape() {
        next = list;
        list = this;
    } //Фигура присоединяется к списку
    virtual point north() const = 0;    //Точки для привязки
    virtual point south() const = 0;

    virtual point east() const = 0;

    virtual point west() const = 0;

    virtual point neast() const = 0;

    virtual point seast() const = 0;

    virtual point nwest() const = 0;

    virtual point swest() const = 0;

    virtual void draw() = 0;    //Рисование
    virtual void move(int, int) = 0;    //Перемещение
    virtual void resize(int) = 0;//Изменение размера
};

shape *shape::list = nullptr;    //Инициализация списка фигур

class rotatable : virtual public shape { //Фигуры, пригодные к повороту
public:
    virtual void rotate_left() = 0;    //Повернуть влево
    virtual void rotate_right() = 0;    //Повернуть вправо
};

class reflectable : virtual public shape { // Фигуры, пригодные
    // к зеркальному отражению
public:
    virtual void flip_horisontally() = 0;    // Отразить горизонтально
    virtual void flip_vertically() = 0;    // Отразить вертикально
};

class line : public shape {
/* отрезок прямой ["w", "e" ].
north( ) определяет точку "выше центра отрезка и так далеко
на север, как самая его северная точка", и т. п. */
protected:
    point w, e;
public:
    line(point a, point b) : w(a), e(b) {};

    line(point a, int L) : w(point(a.x + L - 1, a.y)), e(a) {};

    point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }

    point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point east() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point west() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point neast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point seast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point nwest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    point swest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    void move(int a, int b) {
        w.x += a;
        w.y += b;
        e.x += a;
        e.y += b;
    }

    void draw() { put_line(w, e); }

    void resize(int d) // Увеличение в (d) раз
    {
        e.x += (e.x - w.x) * (d - 1);
        e.y += (e.y - w.y) * (d - 1);
    }
};

#endif //LAB1_SHAPE_H
