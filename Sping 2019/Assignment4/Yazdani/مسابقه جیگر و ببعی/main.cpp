#include <iostream>

#include <cmath>

using namespace std;

void printNumber(long long int number) {
    while (number > 0) {
        cout << number % 10 << " ";
        number /= 10;
    }
}
long long int reverse(long long int n) {
    long long int re, rev = 0;
    while (n != 0) {
        re = n % 10;
        rev = rev * 10 + re;
        n /= 10;
    }
    return rev;
}
int main() {
    long long int length, tempRes, temp;
    int *number;
    bool valid = true;
    cin >> length;
    temp = length - 1;
    number = new int[length];
    long long int intNumber = 0;
    for (int i = 0; i < length; i++) {
        if (i == length / 2) {
            tempRes = intNumber / pow(10, temp + 1);
        }
        cin >> number[i];
        intNumber += pow(10, temp) * number[i];
        temp--;
    }
    if (length % 2 == 0) {
        temp = tempRes * pow(10, length / 2) + reverse(tempRes);
        if (temp > intNumber) {
            printNumber(temp);
        } else {
            tempRes++;
            temp = tempRes * pow(10, length / 2) + reverse(tempRes);
            printNumber(temp);
        }
    } else {
        temp = -1;
        tempRes = tempRes * 10 + number[length / 2];
        while (true) {
            long long int k = pow(10, length / 2);
            temp =  tempRes * k + reverse(tempRes / 10);
            if (temp > intNumber) {
                printNumber(temp);
                break;
            }
            tempRes++;
        }
    }
}