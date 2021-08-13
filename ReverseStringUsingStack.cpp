// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<stack>

using namespace std;

void reverse(char *a)
{
    cout << a << endl;

    int iLen = strlen(a);
    cout << iLen;

    for (int i = 0, j = iLen-1 ; i < iLen/2; i++, j--) {
        char temp;
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;

    }

    cout << "Reversed string" << a;

    
}
int main()
{
    // char temp[] = "Hello";
    // reverse(temp);


    stack<char> mystack;
    char temp[] = "Hello";

    for (int i = 0; i < strlen(temp); i++) {
        mystack.push(temp[i]);
    }


    while (!(mystack.empty()))
    {
        cout << mystack.top();
        mystack.pop();

    }
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
