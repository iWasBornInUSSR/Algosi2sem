#include <iostream>
using namespace std;
#include "src/figure.h"
int main(){
    parallelogram hat(point(10,10), point(18, 16), point(50,16));
 // parallelogram hat(point(10,10), point(18, 16), point(50,16));
 //   cross hat (point(15,15),point(10,10));
    hat.flip_horisontally();
    shape_refresh();
/*    hat.resize(2);
    shape_refresh();
    std::cout << "=== Generated... ===\n";
    std::cin.get(); //Смотреть исходный набор*/
    return 0;
}