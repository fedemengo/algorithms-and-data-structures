#include "xor_list.hpp"
#include <vector>
#include <exception>

/*
void test_at(xor_list<std::string> &l, int index, std::string v) {
	if(l[index] != v){
		throw std::invalid_argument("Expected value " + v + " but got " + l[index]);
	}
}
*/

void test_equal(std::string u, std::string v) {
	if(u != v){
		throw std::invalid_argument("Expected value " + v + " but got " + u);
	}
}


void print(xor_list<std::string> &l){
    for(auto &x : l){
        std::cout << x << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char const *argv[]) {

    srand(time(0));

    xor_list<std::string> l1({});
    xor_list<std::string> l2({});
    std::vector<std::string> check;

    try {
        for(int i=0; i<1000; ++i){
            std::string str = "h";
            str.append(std::to_string(i));
            int index = 0; //rand() % (list.size() + 1);
            l1.push_back(str);
            l2.push_front(str);
            check.push_back(str);
        }
        
        for(int i=0; i<check.size(); i++) {
            //test_at(list, i, check[i]);
        }

        int i = 0;
        for(std::string &str: check){
            test_equal(l1.pop_front(), check[i]);
            ++i;
        }

        std::cout << "OK" << std::endl;

        i = 0;
        for(std::string &str: check){
            test_equal(l2.pop_back(), check[i]);
            ++i;
        }

        i = 0;
        for(auto it = l1.begin(); it != l1.end(); i++, it++){
            test_equal(*it, check[i]);
        }

        std::cout << "OK" << std::endl;

        i = 0;
        for(auto x: l1){
            test_equal(x, check[i]);
            i++;
        }

/*
        while(list.size()){
            int index = rand() % list.size();
            list.remove(index);
            check.erase(check.begin() + index);
            
            for(int i=0; i<list.size(); ++i){
                test_at(list, i, check[i]);
            }
        }
*/
        std::cout << "OK" << std::endl;

    } catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

    return 0;
}
