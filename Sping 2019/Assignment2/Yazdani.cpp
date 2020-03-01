/** Project name : Map Classifier
 *  Author : Motion
 *  Date : 97/ / /
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

typedef struct Record
{
    string className;
    double *properties;
} Record;

/**
 * This functions parse an input file and map class names to class records
 * @argument string : Address of input file
 * @argument int : features' count
 * @argument map that contains all records linked to their class
 */
map<string, vector<Record>> parseFile(string, int);


/**
 * Total number of records existing in the input file, in any class
 * @argument map : result of above function :-/
 * @result number of records
 */
int numberOfRecords(map<string, vector<Record>>);

/**
 * Calculates p(xi|Ck)
 * @argument double(1) : value of xi
 * @argument double(2) : Variance of records ith feature in the desired class
 * @argument double(3) : Average of records ith feature in the desired class
 */
double calculate(double, double, double);


/**
 * Calculates variance of records in desired class
 * @argument vector : all records in desired class
 * @argument double : average of ith feature of all records in desired class
 * @argument int : feature index, or `i`
 */
double variance(vector<Record>, double, int);


/**
 * Calculates average
 * @argument vector : all records in the desired class
 * @argument int : feature index, or `i`
 */
double average(vector<Record>, int);


/**
 * Calculates p(Ck|x)
 * @argument vector : all records in the desired class
 * @argument int(1) : total records count, in all classes
 * @argument int(2) : features count
 * @argument double* : array of features entered by user, in order to classify
 */
double probabilityOfBeingInClass(vector<Record>, int, int, double*);


int main() {
    int featuresCount, classesCount;
    string fileLocation, trash;
    cout << "Enter features count: ";
    cin >> featuresCount;
    cout << "Enter classes count: ";
    cin >> classesCount;
    cout << "Enter file location: ";
    cin >> fileLocation;
    cout << "Enter list of classes (Sepereate with space):";
    for (int i = 0; i < classesCount; i++) cin >> trash;

    map<string, vector<Record>> records = parseFile(fileLocation, featuresCount);
    int recordsCount = numberOfRecords(records);

    while(true) {
        cout << "Enter " << featuresCount << " features and I will guess the class name! Or use Ctrl+C to shut me down :-( :" << endl;
        double *props = new double[featuresCount];
        for (int i = 0; i < featuresCount; i++) {
            cin >> props[i]; // Read features from user
        }
        double max = -1;
        string name;
        for ( auto it = records.begin(); it != records.end(); ++it  ) { // Iterate classes and records
            double probability = probabilityOfBeingInClass(it->second, recordsCount, featuresCount, props);
            if (probability > max) { // Save the maximum value, that's the answer!
                max = probability;
                name = it->first;
            }
        }
        cout << name << endl << endl; // Show the result
    }
    return 0;
}

map<string, vector<Record>> parseFile(string fileLocation, int featuresCount) {
    ifstream file(fileLocation);
    if (!file) throw runtime_error("Cannot open file `" + fileLocation + "`");

    int recordsCount;
    
    file >> recordsCount;
    map<string, vector<Record>> records;
    for (int i = 0; i < recordsCount; i++) {
        Record record;
        record.properties = new double[featuresCount];
        for (int j = 0; j < featuresCount; j++) { // Read features from file
            file >> record.properties[j];
        }
        file >> record.className; // Read record class name from file
        if (records.find(record.className) == records.end()) {
            vector<Record> v;
            v.push_back(record);
            records.insert(pair<string, vector<Record>>(record.className, v));
        } else {
            records.at(record.className).push_back(record);
        }
    }

    return records;
}


double probabilityOfBeingInClass(vector<Record> records, int recordsCount, int featuresCount, double* properties) {
    int recordsInClass = records.size();
    double Pck = recordsInClass / (double)recordsCount; // Calculate P(Ck)
    for (int i = 0; i < featuresCount; i++) {
        double avg = average(records, i);
        double var = variance(records, avg, i);
        Pck *= calculate(properties[i], var, avg);
    }
    return Pck;
}

int numberOfRecords(map<string, vector<Record>> records) {
    int count = 0;
    for(auto elem : records) {
        count += elem.second.size();
    }
    return count;
}

double calculate(double property, double variance, double average) {
    return (1 / sqrt(2 * M_PI * variance)) * exp(-1 * (pow(property - average, 2) / (2 * variance)));
}


double variance(vector<Record> records, double average, int featureIndex) {
    double sum = 0;
    for (int i = 0; i < records.size(); i++) {
        sum += pow((average - records[i].properties[featureIndex]), 2);
    }
    return sum / records.size();
}


double average(vector<Record> records, int featureIndex) {
    double sum = 0;
    for (int i = 0; i < records.size(); i++) sum += records[i].properties[featureIndex];
    return sum / records.size();
}
