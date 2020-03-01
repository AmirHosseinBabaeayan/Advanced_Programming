#include <iostream>
using namespace std;

void swap(int *x, int *y) 
{ 
    int temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void permute(int *a, int x, int y, int l, int r) 
{ 
   int i; 
   if (l == r && a[x] < a[y]) {
       for (int i = 0; i <= r; i++)
            cout << a[i] << " ";
        cout << endl;    
   } else { 
       for (i = l; i <= r; i++) 
       {
          swap((a+l), (a+i)); 
          permute(a, x, y, l+1, r); 
          swap((a+l), (a+i)); 
       } 
   } 
} 

int main() {
    int n, i, j;
    cin >> n >> i >> j;
    int *numbers = new int[n];
    for (int k = 0; k < n; k++) {
        cin >> numbers[k];
    }
    permute(numbers, i, j, 0, n - 1);
}