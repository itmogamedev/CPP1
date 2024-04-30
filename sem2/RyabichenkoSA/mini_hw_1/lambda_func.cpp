#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main(){
	std::vector<std::string> srcVec;
	std::string line;
	int n=0;
	char symbol;
	
	std::cout << "Please enter number of string, and next enter strings"<<std::endl;
	std::cin >> n;

	
	for (int i=0; i<n; i++){ 
	    std::cin >> line;
	    srcVec.push_back(line);
	}
	
	std::cout << "Please enter first symbol"<<std::endl;
	std::cin >> symbol;
	
    for (std::string x : srcVec) std::cout << x << " "; 
    std::cout<<std::endl;
        
    int result = count_if(srcVec.begin(), srcVec.end(), [symbol] (std::string n) {
			return symbol == n[0];
    });

    std::cout << result << std::endl;
}
