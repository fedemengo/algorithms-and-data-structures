#include <bits/stdc++.h>
#include "doubly_linked.hpp"

void print(doubly_linked<std::string> &l){
    for(auto &x : l){
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    int N = atoi(argv[1]);
    srand(time(0));

    doubly_linked<std::string> list({});

    for(int i=0; i<N; ++i){
        std::string str = "h";
        str.append(std::to_string(i));
        list.insert(rand() % (list.size() + 1), str);
        list.print();
    }
    
    //for(std::string str : list){
    //    std::cout << str << std::endl;
    //}

    //for(auto it = list.begin(); it != list.end(); it++){
    //    std::cout << *it << std::endl;
    //}

    while(list.size()){
        list.remove(rand() % list.size());
        //print(list);
        //list.pop_back();
        list.print();
    }

    return 0;
}
