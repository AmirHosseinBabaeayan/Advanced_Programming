#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <cstdlib>

using namespace std;

void insertion(const string* const daste, const int* const n, map<string, double*> &ABCPtr, const double* const row)
{ // This function will insert the row of the dataset we just read, in the results.
    ABCPtr[*daste][0]++;
    // Counting the number of data for any class in dataset.
    for (int j = 1; j <= *n; j++)
    {
        ABCPtr[*daste][j] += row[j - 1];
        // Keeping the sum of any feature for any class, so we can calculate the mean.
        ABCPtr[*daste][*n + j] += row[j - 1] * row[j - 1];
        // Keeping the sum of square roots for any feature for any class, so we can calculate the variance.
    }
}

void read_the_file(const string* const file_path, const int* const n, int* const m, map<string, double*> &ABCPtr)
{ // This function will read the file and stores the information we need from dataset.
    ifstream f;
    f.open((*file_path).c_str(), ios::in);
    if (!f)
    {
        cout << "Unable to open file";
        return; // terminate with error
    }
    f >> *m;
    string daste;
    double row[*n];
    for (int i = 0; i < *m; i++)
    {
        for (int j = 0; j < *n; j++) f >> row[j];
        // In this loop we store the data of a row of the dataset in an array.
        f >> daste;
        // Getting the name of the class.
        insertion(&daste, n, ABCPtr, row);
    }
    f.close();
}

void finishingCalcalus(const int* const n, const int* const m, const string* const daste, map<string, double*> &ABCPtr)
{
    // This function calculate the mean and variance of any feature for any class,
    // from the result of reading the file, and calculate the final results.
    for (int j = 1; j <= *n; j++)
    {
        ABCPtr[*daste][j] /= ABCPtr[*daste][0]; // now the mean is ready.
        ABCPtr[*daste][*n + j] /= ABCPtr[*daste][0];
    }
    for (int j = 1; j <= *n; j++)
    {
        ABCPtr[*daste][*n + j] -= ABCPtr[*daste][j] * ABCPtr[*daste][j]; // Now the variance is ready.
    }
    ABCPtr[*daste][0] /= *m; // Now the P(Ck) is ready for use.
}

void prepareTheResults(const string* const namesPtr, const int* const n, const int* const K, map<string, double*> &ABCPtr)
{ // This function will prepare the results we need from the dataset.
    cout << "Please insert the dataset file path: ";
    string file_path;
    cin >> file_path;
    int m;
    read_the_file(&file_path, n, &m, ABCPtr);
    for (int i = 0; i < *K; i++)
    {
        string daste = namesPtr[i];
        finishingCalcalus(n, &m, &daste, ABCPtr);
    }
}

void calculate(const int* const n, double* const z, const double* const row, const string* const daste, map<string, double*> &ABCPtr)
{ // This function will calculate the p(C|k)
    double power, p;
    for (int j = 0; j < *n; j++)
    {
        power = row[j] - ABCPtr[*daste][j + 1];
        power *= -power;
        power /= 2 * ABCPtr[*daste][*n + j + 1];
        p = exp(power);
        p /= sqrt(2 * 3.1415 * ABCPtr[*daste][*n + j + 1]);
        *z *= p;
    }
}

void MAP(const string* const namesPtr, const int* const n, const int* const K, int* const index, const double* const row, map<string, double*> &ABCPtr)
{ // This function will find the most possible class with "MAP" method.
    double y = 0, z;
    for (int k = 0; k < *K; k++)
    {
        string daste = namesPtr[k]; // This is the name of the certain class.
        z = ABCPtr[daste][0]; // p(Ck)
        calculate(n, &z, row, &daste, ABCPtr);
        if (z > y)
        {
            *index = k;
            y = z;
        }
    }
}

void predict(const string* const namesPtr, const int* const n, const int* const K, map<string, double*> &ABCPtr)
{ // This function get the unknown cases and predicts their class.
    cout << "Please tell me how many samples you have? ";
    int number; // the number of unknown cases.
    double row[*n];
    cin >> number;
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < *n; j++) cin >> row[j];
        // This loop reads a case from input.
        int index = 0; // This is the  index of the most possible class.
        MAP(namesPtr, n, K, &index, row, ABCPtr);
        cout << "The most possible class, is: " << namesPtr[index] << endl;
    }
}


void getNumbers(int* const nPtr, int* const KPtr)
{ // Here we get the number of features and classes.
    cout << "How many features there are?" << endl;
    cin >> *nPtr;
    cout << "How many classes there are?" << endl;
    cin >> *KPtr;
}

void getNames(string * const namesPtr, const int* const K, const int* const n, map<string, double*> &ABC)
{ // Here we get name of all of the classes.
    cout << "Please insert the classes one by one bellow." << endl;
    for (int i = 0; i < *K; i++)
    {
        cout << i + 1 << " ";
        cin >> namesPtr[i];
        ABC[namesPtr[i]] = (double*)malloc((2 * *n + 1) * sizeof(double));
        for (int j = 0; j <= 2 * *n; j++) ABC[namesPtr[i]][j] = 0;
    }
}

int main()
{
    int n, K;
    map<string, double*> result;
    /*
    The "results" for any class will be like this:
    the first element: Nk / m --> p(Ck)
    the next n elements: mean of any feature for the class
    the next n elements: variance of any feature for the class
    */
    getNumbers(&n, &K);
    string names[K];// This will keep the names of classes
    getNames(names, &K, &n, result);
    prepareTheResults(names, &n, &K, result);
    predict(names, &n, &K, result);
    return 0;
}
