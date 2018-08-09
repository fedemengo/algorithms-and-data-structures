#include <bits/stdc++.h>
#include "single_linked.hpp"

void print(single_linked<std::string> &l){
    for(auto &x : l){
        std::cout << std::setw(2) << x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    int N = atoi(argv[1]);
    srand(time(0));

    single_linked<std::string> list({});

    for(int i=0; i<N; ++i){
        std::string str = "h";
        str.append(std::to_string(i));
        list.insert(rand() % (list.size() + 1), str);
        //list.push_back(str);
        list.print();
    }


    while(list.size()){
        list.remove(rand() % list.size());
        //list.pop_back();
        //print(list);
        list.print();
    }

    return 0;
}
