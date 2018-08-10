#include "doubly_linked.hpp"
#include <vector>
#include <exception>

void test_at(doubly_linked<std::string> &l, int index, std::string v) {
	if(l[index] != v){
		throw std::invalid_argument("Expected value " + v + " but got " + l[index]);
	}
}

void test_equal(std::string u, std::string v) {
	if(u != v){
		throw std::invalid_argument("Expected value " + v + " but got " + u);
	}
}

void print(doubly_linked<std::string> &l){
    for(auto &x : l){
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {

    srand(time(0));

    doubly_linked<std::string> list({});
    std::vector<std::string> check;

    try {
        for(int i=0; i<1000; ++i){
            std::string str = "h";
            str.append(std::to_string(i));
            int index = rand() % (list.size() + 1);
            list.insert(index, str);
            check.insert(check.begin() + index, str);
        }
        
        for(int i=0; i<check.size(); i++) {
            test_at(list, i, check[i]);
        }

        int i = 0;
        for(std::string &str: list){
            test_equal(str, check[i]);
            ++i;
        }

        i = 0;
        for(auto it = list.begin(); it != list.end(); i++, it++){
            test_equal(*it, check[i]);
        }

        while(list.size()){
            int index = rand() % list.size();
            list.remove(index);
            check.erase(check.begin() + index);
            
            for(int i=0; i<list.size(); ++i){
                test_at(list, i, check[i]);
            }
        }

        std::cout << "OK" << std::endl;

    } catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

    return 0;
}
