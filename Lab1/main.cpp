#include <iostream>
using namespace std;
#include "src/figure.h"
int main(){
    parallelogramWithCross hat(point(10,10),point(50,16),10, true);
//    rectangle hat1(point(10,10),point(50,16));
 // parallelogram hat(point(10,10), point(18, 16), point(50,16));
 //   cross hat (point(15,15),point(10,10));
    shape_refresh();
    hat.rotate_left();
    shape_refresh();
    hat.rotate_left();
    shape_refresh();
/*    hat.resize(2);
    shape_refresh();
    std::cout << "=== Generated... ===\n";
    std::cin.get(); //Смотреть исходный набор*/
    return 0;
}