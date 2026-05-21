
#include <iostream>
#include <string>

const int inverse[31] = {0,1,16,21,8,25,26,9,4,7,28,17,13,12,20,29,2,11,19,18,14,3,24,27,22,5,6,23,10,15,30};

int main(){
    std::string pass;
    std::cin >> pass;
    if (pass == "send"){
        int k;
        std::cin >> k;
        int k1 = k % 30 + 1, k2 = k / 30 + 1;
        for (int x = 1; x <= 30; ++x){
            std::cout << x + 31 * ((k1 * x + k2) % 31);
            if (x == 30) std::cout << std::endl;
            else std::cout << ' ';
        }
    }
    else{
        int a, b;
        std::cin >> a >> b;
        int x1 = a % 31, y1 = a / 31, x2 = b % 31, y2 = b / 31;
        int k1 = (y2-y1+31)*inverse[(x2-x1+31)%31]%31;
        int k2 = (y1-k1*x1+31*31)%31;
        std::cout << (k1-1)+30*(k2-1) << std::endl;
    }
    return 0;
}
