#include <bits/stdc++.h>

using namespace std;

class DropCheck{
    public:
    bool productReleased(){
        random_device rd;
        uniform_int_distribution<int> dist(1,10);
        if(dist(rd)==1){
            return false;
        }
        else
        return true;
    }
};