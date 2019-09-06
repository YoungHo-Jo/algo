#include <iostream>
#define MAX 1000000

using namespace std;


int main(void) {
    // get string
    char str[MAX];
    gets(str);
    
    // lead blank
    int blankNum = 0;
    for(int i = 0; i < MAX; i++) {
        if(str[i] == '\0') {
            if(i != 0) {
                blankNum++;
            } 
            break;
        } else {
            if(str[i] == ' ') {
                blankNum++;
                continue;
            }
        }
    } 

    // put result
    cout << blankNum << endl;


    return 0;
}