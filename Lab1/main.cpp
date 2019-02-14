#include <iostream>
using namespace std;
#include "src/figure.h"
int main(){
    parallelogram hat(point(10,10), point(18, 16), point(30,16));
    shape_refresh( );
    hat.rotate_left();
    shape_refresh();
/*    hat.resize(2);
    shape_refresh();
    std::cout << "=== Generated... ===\n";
    std::cin.get(); //Смотреть исходный набор*/
    return 0;
}