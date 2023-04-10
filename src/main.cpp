#include <iostream>
#include "lib/mainClass.h"
#include "lib/subClass.h"


int main(int argc, char **argv) {
    forward_spisok<int> sp(10);
    sp.push_back(12);
    std::cout << sp;
}
