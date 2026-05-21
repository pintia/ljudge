
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>

const int inverse[31] = {0,1,16,21,8,25,26,9,4,7,28,17,13,12,20,29,2,11,19,18,14,3,24,27,22,5,6,23,10,15,30};

std::pair<std::vector<int>, std::vector<int>> shuffle(int maxa){
    std::vector<int> pa(maxa+1), qa(maxa+1);
    for (int i = 1; i <= maxa; ++i) pa[i] = i;
    for (int i = 1; i <= 10*maxa; ++i){
        int i1 = rand()%maxa+1, i2 = rand()%maxa+1;
        if (i1 != i2) std::swap(pa[i1], pa[i2]);
    }
    for (int i = 1; i <= maxa; ++i) qa[pa[i]] = i;
    return {pa, qa};
}

int main(){
    int maxk = 600, maxa = 1000;
    std::pair<std::vector<int>, std::vector<int>> psa = shuffle(maxa), psk = shuffle(maxk);
    std::vector<int> &pa = psa.first, &qa = psa.second, &pk = psk.first, &qk = psk.second;
    
    std::string pass;
    std::cin >> pass;
    if (pass == "send"){
        int k;
        std::cin >> k;
        k = pk[k];
        int k1 = k % 30 + 1, k2 = k / 30 + 1;
        for (int x = 1; x <= 30; ++x){
            std::cout << pa[x + 31 * ((k1 * x + k2) % 31)];
            if (x == 30) std::cout << std::endl;
            else std::cout << ' ';
        }
    }
    else{
        int a, b;
        std::cin >> a >> b;
        a = qa[a]; b = qa[b];
        int x1 = a % 31, y1 = a / 31, x2 = b % 31, y2 = b / 31;
        int k1 = (y2-y1+31)*inverse[(x2-x1+31)%31]%31;
        int k2 = (y1-k1*x1+31*31)%31;
        std::cout << qk[(k1-1)+30*(k2-1)] << std::endl;
    }
    return 0;
}
