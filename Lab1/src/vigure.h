//
// Created by picknick on 06.02.19.
//

#ifndef LAB1_VIGURE_H
#define LAB1_VIGURE_H

#include "shape.h"
class rectangle : public rotatable {
/* nw ------ n ------ ne
   |		          |
   |		          |
   w	     c            e
   |		          |
   |		          |
   sw ------ s ------ se */
protected:
    point sw, ne;
public:
    rectangle(point a, point b) : sw(a), ne(b) {}

    point north() const { return point((sw.x + ne.x) / 2, ne.y); }

    point south() const { return point((sw.x + ne.x) / 2, sw.y); }

    point east() const { return point(ne.x, (sw.y + ne.y) / 2); }

    point west() const { return point(sw.x, (sw.y + ne.y) / 2); }

    point neast() const { return ne; }

    point seast() const { return point(ne.x, sw.y); }

    point nwest() const { return point(sw.x, ne.y); }

    point swest() const { return sw; }

    void rotate_right() // Поворот вправо относительно se
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        sw.x = ne.x - h * 2;
        ne.y = sw.y + w / 2;
    }

    void rotate_left() // Поворот влево относительно sw
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        ne.x = sw.x + h * 2;
        ne.y = sw.y + w / 2;
    }

    void move(int a, int b) {
        sw.x += a;
        sw.y += b;
        ne.x += a;
        ne.y += b;
    }

    void resize(int d) {
        ne.x += (ne.x - sw.x) * (d - 1);
        ne.y += (ne.y - sw.y) * (d - 1);
    }

    void draw();
};

void rectangle::draw() {
    put_line(nwest(), ne);
    put_line(ne, seast());
    put_line(seast(), sw);
    put_line(sw, nwest());
}

void shape_refresh() // Перерисовка всех фигур
{
    screen_clear();
    for (shape *p = shape::list; p; p = p->next) p->draw();
    screen_refresh();
}

void up(shape &p, const shape &q) // поместить p над q
{    //Это ОБЫЧНАЯ функция, а не член класса!
    point n = q.north();
    point s = p.south();
    p.move(n.x - s.x, n.y - s.y + 1);
}

#endif //LAB1_VIGURE_H
