#include <iostream>

using namespace std;

int main() {
    
    int a, b, c;
    int summ, ave;
    
    cout<<"Enter the score for Exam 1: ";cin >> a;
    
    cout<<"Enter the score for Exam 2: ";cin >> b;
    
    cout<<"Enter the score for Exam 3: ";cin >> c;
    
    summ = a + b + c;
    ave = summ / 3;
    
    cout<<"Average Score: " << ave << endl;
    
    if (ave < 70) {
        cout<<"Result: Failed" << endl;
    } else {
        cout<<"Result: Passed" << endl;
    }
    
    return 0;
}
