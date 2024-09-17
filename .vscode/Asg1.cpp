#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
    vector<string> messages ({"hello","my","first","vector","in","c++"});
    for(auto s : messages){
        cout << s << endl;
    }
    return 0;
}