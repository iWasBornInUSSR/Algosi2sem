//
// Created by picknick on 06.02.19.
//

#ifndef LAB1_VIGURE_H
#define LAB1_VIGURE_H
#include "shape.h"
void shape_refresh() // Перерисовка всех фигур
{
    screen_clear();
    for (shape *p = shape::list; p; p = p->next) p->drawWithException();
    screen_refresh();
}
class rectangle : public rotatable {
/* nw ------ n ------ ne
   |		          |
   |		          |
   w	     c        e
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

// ----------------
/*           n
             |
             |
    w -------c------- e
             |
             |
             s
   */
//!Issue: нельзя вычислить w и e если n и w заданы неправильно
class cross : virtual shape {
protected :
    point n;
    point w;
public:
    cross(point a, point b) : n(a),w(b){ }

    point north() const override {
        return point(n);
    }

    point south() const override {
        return point(n.x, n.y - 2 *( (n.y - w.y) )); // (n.y - w.y ) == расстояние от n до с
    }

    point east() const override {
        return point(w.x + 2 * (n.x - w.x ),w.y); // (n.y - w.y ) == расстояние от w до с
    }

    point west() const override {
        return point(w);
    }
    point neast() const override {
        return point(east().x,n.y);
    }

    point seast() const override {
        return point(east().x,south().y);
    }

    point nwest() const override {
        return point(w.x,n.y);
    }

    point swest() const override {
        return point(w.x,south().y);
    }
    void draw() override {
        put_line(cross::north(),cross::south());
        put_line(cross::west(),cross::east());
    }
    void move(int a, int b) override {
        n.x += a;
        n.y += b;
        w.x += a;
        w.y += b;
    }
    void resize(int d) override {
        n.y += (n.y - w.y) * (d - 1);
        w.x -= (n.x - w.x) * (d - 1);
    }

};

/*      nw ------ n -------- ne
       /		            /
      /                   /
   	 w        c         e
   /		          /
  /		            /
sw ------ s ------ se */
class parallelogram : public rectangle, reflectable{
protected:
    int h;
    bool sideX;
    bool horizontal;
public:
    parallelogram(point a, point b ,int h, bool sideX) : rectangle(a,b) , h(h), sideX(sideX) {
        horizontal = true;
    }

public:
    void draw() override {
        point newNW(nwest().x + horizontal * sideX * h,nwest().y + sideX * !horizontal * h);
        point newNE(ne.x - horizontal * !sideX * h,ne.y - !horizontal * !sideX * h);
        point newSW(sw.x + horizontal * !sideX * h,sw.y + !horizontal * !sideX * h);
        point newSE(seast().x - horizontal * sideX * h,seast().y - sideX * !horizontal * h);
        put_line(newNW,newNE);
        put_line(newNE, newSE);
        put_line(newSE, newSW);
        put_line(newSW, newNW);
    }
    void resize(int d) override {
        rectangle::resize(d);
        h = h * d;
    }

    void rotate_left() override {
        rectangle::rotate_left();
        horizontal = !horizontal;
        sideX = !sideX;
    }

    void rotate_right() override {
        rectangle::rotate_right();
        horizontal = !horizontal;
        sideX = !sideX;
    }

    void flip_horisontally() override {
        sideX = !sideX;
    }

    void flip_vertically() override {
        flip_horisontally();
    }

};
/*      nw ---k-- n -------- ne
       /	  |             /
      /       |           /
   	 w--------c---------e
   /		  |       /
  /		      |     /
sw ------ s --t--- se */
class parallelogramWithCross : public parallelogram , private cross { // Использую приватное наследование, чтобы был доступ к приватным членам
public:
    parallelogramWithCross(point a, point b ,int h, bool sideX) : parallelogram(a, b, h,sideX),
    cross(point((parallelogram::west().x + parallelogram::east().x)/2,parallelogram::north().y),point(sw.x + h / 2,parallelogram::west().y)) {
    }
    // point((west().x + east().x)/2,north().y) - координаты точки k
    // По х это координаты х центра, по y координаты по y севера

    void draw() override {
        parallelogram::draw();
        cross::draw();  //! north() и south() беруться из paral а не из cross
    }

public:
    point north() const override {
        return parallelogram::north();
    }

    point south() const override {
        return parallelogram::south();
    }

    point east() const override {
        return parallelogram::east();
    }

    point west() const override {
        return parallelogram::west();
    }

    point neast() const override {
        return parallelogram::neast();
    }

    point seast() const override {
        return parallelogram::seast();
    }

    point nwest() const override {
        return parallelogram::nwest();
    }

    point swest() const override {
        return parallelogram::swest();
    }

    void flip_horisontally() override {
        parallelogram::flip_horisontally();
    }

    void move(int a, int b) override {
        parallelogram::move(a, b);
        cross::move(a,b);
    }

    void resize(int d) override {
        parallelogram::resize(d);
       crossCoordinateOverride();
    }


    void rotate_left() override {
        parallelogram::rotate_left();
        crossCoordinateOverride();
    }

    void rotate_right() override {
        parallelogram::rotate_right();
        crossCoordinateOverride();
    }

private:
    void crossCoordinateOverride() {
        // Если параллелограмм в "горизонтальном состоянии"
        if (horizontal) {
            cross::n.x = (parallelogram::west().x + parallelogram::east().x) / 2;
            cross::n.y = parallelogram::north().y;
            cross::w = point(sw.x + h / 2,parallelogram::west().y);
        } else {         // Если параллелограмм в "вертикальном состоянии"
            cross::w = parallelogram::west();
            cross::n.x = parallelogram::north().x;
            cross::n.y = parallelogram::north().y - h / 2 ;
        }
    }
};
class myshape : public rectangle {
//Моя фигура ЯВЛЯЕТСЯ прямоугольником
    int w, h;
    line l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
    line r_eye; // правый глаз
    line mouth; // рот
public:
    myshape(point, point);
    void draw( );
    void move(int, int);
    void resize(int) { }
};
myshape :: myshape(point a, point b)
        : rectangle(a, b),
          w(neast( ).x - swest( ).x + 1),
          h(neast( ).y - swest( ).y + 1),
          l_eye(point(swest( ).x + 2, swest( ).y + h * 3 / 4), 2),
          r_eye(point(swest( ).x + w - 4, swest( ).y + h * 3 / 4), 2),
          mouth(point(swest( ).x + 2, swest( ).y + h / 4), w - 4)
{ }
void myshape :: draw( )
{
rectangle :: draw( );
int a = (swest( ).x + neast( ).x) / 2;
int b = (swest( ).y + neast( ).y) / 2;
put_point(point(a, b));
}
void myshape :: move(int a, int b)
{
    rectangle :: move(a, b);
    l_eye.move(a, b);
    r_eye.move(a, b);
    mouth.move(a, b);
}
class h_circle: public rectangle, public reflectable {
    bool reflected;
public:
    h_circle(point a, point b, bool r=true) : rectangle(a, b), reflected(r) { }
    void draw();
    void flip_horisontally( ) { };
// Отразить горизонтально
    void flip_vertically( ) { reflected = !reflected; };
// Отразить вертикально
};
void h_circle :: draw() //Алгоритм Брезенхэма для окружностей
{ int x0 = (sw.x + ne.x)/2;
    int y0 = reflected ? sw.y : ne.y;
    int radius = (ne.x - sw.x)/2;
    int x = 0;
    int y = radius;
    int delta = 2 - 2 * radius;
    int error = 0;
    while(y >= 0) {
        if(reflected) { put_point(x0 + x, y0 + y*0.7); put_point(x0 - x, y0 + y*0.7); }
        else { put_point(x0 + x, y0 - y*0.7); put_point(x0 - x, y0 - y*0.7); }
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) { ++x; delta += 2 * x + 1; continue; }
        error = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0) { --y; delta += 1 - 2 * y; continue; }
        ++x; delta += 2 * (x - y); --y;
    }
}
void up(shape &p, const shape &q) // поместить p над q
{    //Это ОБЫЧНАЯ функция, а не член класса!
    point n = q.north();
    point s = p.south();
    p.move(n.x - s.x, n.y - s.y + 1);
}
void down(shape &p, const shape &q)
{ point n = q.south( );
    point s = p.north( );
    p.move(n.x - s.x, n.y - s.y - 1);
}
#endif //LAB1_VIGURE_H
