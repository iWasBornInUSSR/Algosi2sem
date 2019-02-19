//
// Created by picknick on 06.02.19.
//

#ifndef LAB1_VIGURE_H
#define LAB1_VIGURE_H
// TODO:
//  -create figure parallelogram
//  -combine them
#include "shape.h"
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
class cross : shape {
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
/*      nw ------ n -------- ne
       /		            /
      /                   /
   	 w        c         e
   /		          /
  /		            /
sw ------ s ------ se */
class parallelogram : rotatable, reflectable{
protected:
    point nw;
    point sw;
    point ne;
public:
    parallelogram(point a, point b ,point c) : sw(a),nw(b),ne(c) {}

    point north() const override {
        return point((ne.x + nw.x) / 2, (ne.y + nw.y) / 2); // (ne.x -nw.x) / 2 - середина отрезка
    }

    point south() const override {
        return point((seast().x + sw.x) / 2, (seast().y + sw.y) / 2);
    }

    point east() const override {
        return point( (ne.x + seast().x) / 2,(ne.y + seast().y) / 2 );
    }

    point west() const override {
        return point((nw.x + sw.x) / 2,(nw.y + sw.y) / 2);
    }

    point neast() const override {
        return ne;
    }

    point seast() const override {
        return point(ne.x - nw.x + sw.x,ne.y - nw.y + sw.y);
    }

    point nwest() const override {
        return nw;
    }

    point swest() const override {
        return sw;
    }

    void draw() override {
        put_line(nw, ne);
        put_line(ne, seast());
        put_line(seast(), sw);
        put_line(sw, nw);
    }

    void move(int a, int b) override {
        nw.x += a;
        nw.y += b;
        sw.x += a;
        sw.y += b;
        ne.x += a;
        ne.y += b;

    }

    void resize(int d) override {
        ne.x += (ne.x - sw.x) * (d - 1);
        ne.y += (ne.y - sw.y) * (d - 1);
        nw.x += (nw.x - sw.x) * (d - 1);
        nw.y += (nw.y - sw.y) * (d - 1);
    }

    void rotate_left() override {
       int dx = (nw.x - sw.x);
       int dy = (nw.y - sw.y);
        nw.x = -dy + sw.x;
        nw.y = dx + sw.y;

        dy = ne.y - sw.y;
        dx = ne.x - sw.x;
        ne.x = -dy + sw.x;
        ne.y = dx + sw.y;
    }

    void rotate_right() override {
        point se = seast();
        int dx = (nw.x - se.x);
        int dy = (nw.y - se.y);
        nw.x =  dy + se.x;
        nw.y = -dx + se.y;

        dx =  ne.x - se.x;
        dy =  ne.y - se.y;
        ne.x = dy + se.x;
        ne.y = -dx + se.y;

        dx =  sw.x - se.x;
        dy =  sw.y - se.y;
        sw.x = dy + se.x;
        sw.y = -dx + se.y;
    }

    void flip_horisontally() override {
        int buf1 =  seast().x;
        int buf = sw.x;
        sw.x = nw.x;
        nw.x = buf;
        ne.x = buf1;
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
class parallelogramWithCross : parallelogram , private cross { // Использую приватное наследование, чтобы был доступ к приватным членам
public:
    parallelogramWithCross(point a, point b, point c) : parallelogram(a, b, c),
    cross(point((parallelogram::west().x + parallelogram::east().x)/2,parallelogram::north().y),parallelogram::west()) {
    //cross(parallelogram::north(),parallelogram::west()) {
    } // point((west().x + east().x)/2,north().y) - координаты точки k
    // По х это координаты х цента, по y координаты по y севера

    void draw() override {
        parallelogram::draw();
        cross::draw();  //! north() и south() беруться из paral а не из cross
    }

public:
    void move(int a, int b) override {
        parallelogram::move(a, b);
        cross::move(a,b);
    }

    void resize(int d) override {
        parallelogram::resize(d);
        cross::resize(d);
    }

    void rotate_left() override {
        parallelogram::rotate_left();
        crossCoordinateOverride();
    }

    void rotate_right() override {
        parallelogram::rotate_right();
        crossCoordinateOverride();
    }

    void flip_horisontally() override {
        parallelogram::flip_horisontally();

    }

    void flip_vertically() override {
        parallelogram::flip_vertically();
    }

private:
    void crossCoordinateOverride() {
        // Если параллелограмм в "горизонтальном состоянии"
        if(parallelogram::west().y == parallelogram::east().y){
            cross::n.x = (parallelogram::west().x + parallelogram::east().x)/2;
            cross::n.y = parallelogram::north().y;
            cross::w = parallelogram::west();
        } else {         // Если параллелограмм в "вертикальном состоянии"
            cross::w.y = (parallelogram::west().y + parallelogram::east().y)/2;
            cross::w.x = parallelogram::north().x;
            cross::n = parallelogram::east();
        }
/*        // Ищем точку с максимальной координатой по y , она будет севером
   cross::n = max({parallelogram::north(),parallelogram::south(),parallelogram::east(),parallelogram::west()});
        // Ищем точку с минимальной координатой по x , она будет востоком
   cross::w = min({parallelogram::north(),parallelogram::south(),parallelogram::east(),parallelogram::west()});*/
    }

/*    point max(initializer_list<point> initializerList) {
       point max(0,-YMAX);
       for(auto c : initializerList)
           if(c.y > max.y) max = c;
        return max;
    }
    point min(initializer_list<point> initializerList) {
        point min(XMAX + 1,0);
        for(auto c : initializerList)
            if(c.x < min.x) min = c;
        return min;
    }*/
};
#endif //LAB1_VIGURE_H
