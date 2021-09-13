#include <iostream>
#include <string>

int main() {
    size_t n =0, k =0 ;
	char c;
	std::string s;
	std::cin >> n;
    for (size_t i = 0; i < n; i++) {
		std::cin >> k;
        std::cin >> s;
		for(size_t j=0; j<k; j++){
			c = s[j];
			if(c == 'U'){
				c = 'D';
			}else if( c == 'D'){
				c = 'U';
			}
			std::cout << c;
		}
		std::cout << "" << std::endl;
    }
	return 0;
}