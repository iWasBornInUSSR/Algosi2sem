#include <iostream>
using namespace std;
#include "src/vigure.h"
int main(){
    rectangle hat(point(XMAX,0 ), point(0, 0));
    shape_refresh( );
    std::cout << "=== Generated... ===\n";
    std::cin.get(); //Смотреть исходный набор
    return 0;
}