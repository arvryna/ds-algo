// Solution https://codeforces.com/contest/1569/problem/A
// 9-9-2021

#include <iostream>
#include <string>

int main() {
    int x = 0;
    int l = 0;
    std::string in_str;
    std::cin >> x;
    for (int i = 0; i < x; i++) {
        std::cin >> l;
        std::cin >> in_str;
        for(int j=0; j<l; j++){
            if(j == l-1){
                std::cout << "-1 -1" << std::endl;
            }else{
                if (in_str[j] == 'a' && in_str[j+1] == 'b'){
                    std::cout << j+1 << " " << j+1+1 << std::endl;
                    break;
                }else if( in_str[j] == 'b' && in_str[j+1] == 'a'){
                    std::cout << j+1 << " " << j+1+1 << std::endl;
                    break;
                }
            }
        }
    }
    return 0;
}

