#include <iostream>
using namespace std;
#include "src/figure.h"
int main(){
/*    parallelogram upper(point(10, -6), point(34, 10),4, false);
    parallelogramWithCross downer(point(5, 4), point(-34, 10),4, false);*/
    rectangle hat(point(-2, -2), point(XMAX - 3, YMAX - 3));
 //   line brim(point(0,15),17);
 //   myshape face(point(15,134), point(27,18));
    //== 2.Ориентация ==
/*    hat.rotate_right( );
    brim.resize(2);
    face.resize(2);
    downer.flip_vertically();
//== 3.Сборка изображения ==
    face.move(0, 10); // В исходное положение
    up(brim, face);
    up(hat, brim);
    down(downer, face);
    up(upper,hat);*/
    shape_refresh( );
    std::cout << "=== Generated... ===\n";
/*    rectangle hat(point(-5,-5),point (10,10));
    shape_refresh();*/
    return 0;
}