//
//  main.cpp
//  AvLL
//
//  Created by Sunil Thunuguntla on 6/16/13.
//  Copyright (c) 2013 Sunil Thunuguntla. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <string.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

static inline unsigned long long tick()
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

static unsigned long long res;

int size[16] = {10, 50, 100, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 10000, 100000, 1000000};


int length (int A[]) {
    return (sizeof(A)/sizeof (int));
}

string getString (unsigned long long num) {
    stringstream sstm;
    sstm << num;
    return sstm.str();
}

void print (list<int> &L) {
    if (L.size() == 0) {
        ////cout << "Empty" << endl ;
        return;
    }
    list<int>::iterator itr;
    for (itr = L.begin(); itr != L.end(); itr++) {
        //cout << *itr << ", ";
    }
    ////cout << endl;
}

int getValueFromPercent (int percent, int maxValue) {
    int v = (percent*maxValue)/100;
    v = (v == 0 ? maxValue : v);
    return v;
}

void print (vector<int> &A, int dataSize) {
    for (int i = 0; i < dataSize; i++) {
        //cout << A[i] << ", ";
    }
    ////cout << endl;
}

void doFrontInsert (list<int> &L, int numTimes, int maxSize) {
    if (L.size() >= maxSize) return;
    for (int i = 0; i < numTimes; i++) {
        L.push_front(i);
    }
    //cout << numTimes << " Inserts" << ", Size = " << L.size() << endl;
    //print (L);
}

void doTailInsert (list<int> &L, int numTimes, int maxSize) {
    if (L.size() >= maxSize) return;
    for (int i = 0; i < numTimes; i++) {
        L.push_back(i);
    }
    //cout << numTimes << " Inserts" << ", Size = " << L.size() << endl;
    //print (L);
}

void doRandomInsert (list<int> &L, int numTimes, int maxSize) {
    if (L.size() >= maxSize) return;
    for (int i = 0; i < numTimes; i++) {
        int position = rand()%(L.size() == 0 ? 1 : L.size());
        list<int>::iterator itr = L.begin();
        advance(itr, position);
        L.insert(itr, 10);
    }
    //cout << numTimes << " Random Inserts" << ", Size = " << L.size() << endl;
    //print (L);
}

void doFrontInsert (vector<int> &A, int numTimes, int maxSize) {
    for (int i = 0; i < numTimes; i++) {
        A.insert(A.begin(), 10);
    }
    //cout << numTimes << " Inserts" << endl;
    //print (A, maxSize);
}

void doTailInsert (vector<int> &A, int numTimes, int maxSize) {
    for (int i = 0; i < numTimes; i++) {
        A.insert(A.end(), 10);
    }
    //cout << numTimes << " Inserts" << endl;
    //print (A, maxSize);
}

void doRandomInsert (vector<int> &A, int numTimes, int maxSize) {
    for (int i = 0; i < numTimes; i++) {
        A.insert(A.begin()+(rand()%(A.size() == 0 ? 1 : A.size())), 10);
    }
    //cout << numTimes << " Inserts" << endl;
    //print (A, maxSize);
}

void doUpdate (list<int> &L, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        int j = rand() % (L.size() == 0 ? 1 : L.size());
        list<int>::iterator itr = L.begin();
        advance(itr, j);
        *itr = 30;
    }
    //cout << numTimes << " Updates" << endl;
    //print (L);
}

void doUpdate (vector<int> &A, int numTimes, int maxSize) {
    for (int i = 0; i < numTimes; i++) {
        int j = rand() % maxSize;
        A[j] = 30;
    }
    //cout << numTimes << " Updates" << endl;
    //print (A, maxSize);
}

void doSelect (list<int> &L, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        int j = rand() % L.size();
        list<int>::iterator itr = L.begin();
        advance(itr, j);
        int k = *itr;
        //////cout << *itr << ", ";
    }
    //cout << numTimes << " Selects" << endl;
}

void doSelect (vector<int> &A, int numTimes, int maxSize) {
    for (int i = 0; i < numTimes; i++) {
        int j = rand() % maxSize;
        int k = A[j];
        //////cout << A[j] << ", ";
    }
    //cout << numTimes << " Selects" << endl;
}

int main(int argc, char* argv[]) {
    clock_t t1, t2;
    if (argc <= 5) {
        ////cout << "usage: AvLL -s SIZE -t [array | ll] [-ni numInserts] [-nu numUpdates] [-ns numSelects]";
        return 0;
    }
    
    long long totalRes = tick();
    
    //For creating the CSV
    string h1 = "Size,Selects,,Random Inserts,,Inserts at Front,,Inserts at end,,Updates,\n";
    string h2 = ",Linked List ,Array,Linked List,Array,Linked List,Array,Linked List,Array,Linked List,Array\n";
    string data = "";
    
    for (int sizeIndex = 0; sizeIndex < 16; sizeIndex++) {
        int dataSize = size[sizeIndex];
        long long updateACycles = 0, insertRACycles = 0, insertFACycles = 0, insertTACycles = 0, selectACycles = 0;
        long long updateLCycles = 0, insertRLCycles = 0, insertFLCycles = 0, insertTLCycles = 0, selectLCycles = 0;
        string sizeofds = "";
        cout << "DataSize =" << dataSize << " --------------" << endl;
        vector<int> A(dataSize);
        list <int> L;
        int iterations = 30;
        if (dataSize > 10000)
            iterations = 1;
        for (int s = 0; s<= iterations; s++) {
            t1 = clock();
            ////cout <<"########### Array ############ "<<endl;
            for  (int i = 1; i < argc-1; i++) {
                if (strcmp("-nri", argv[i]) == 0) {
                    res = tick();
                    doRandomInsert(A, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertRACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nfi", argv[i]) == 0) {
                    res = tick();
                    doFrontInsert(A, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertFACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nti", argv[i]) == 0) {
                    res = tick();
                    doTailInsert(A, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertTACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nu", argv[i]) == 0) {
                    res = tick();
                    doUpdate(A, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        updateACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-ns", argv[i]) == 0) {
                    res = tick();
                    doSelect(A, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        selectACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                }
            }
            ////cout <<"###########" << endl;
            t2 = clock();
        }
        cout << "Array Done" << endl;
        for (int s = 0; s<= iterations; s++) {
            t1 = clock();
            ////cout <<"######### LinkedList ############ "<<endl;
            for  (int i = 1; i < argc-1; i++) {
                if (strcmp("-nri", argv[i]) == 0) {
                    res = tick();
                    doRandomInsert(L, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertRLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nfi", argv[i]) == 0) {
                    res = tick();
                    doFrontInsert(L, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertFLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nti", argv[i]) == 0) {
                    res = tick();
                    doTailInsert(L, getValueFromPercent(atoi(argv[i+1]), dataSize), dataSize);
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        insertTLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nu", argv[i]) == 0) {
                    res = tick();
                    doUpdate(L, atoi(argv[i+1]));
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        updateLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-ns", argv[i]) == 0) {
                    res = tick();
                    doSelect(L, atoi(argv[i+1]));
                    if (s > 4 || iterations == 1) {
                        //ignore first 5 iterations
                        selectLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                }
            }
            ////cout <<"###########" << endl;
            t2 = clock();
        }
        cout << "Linked List Done" << endl;
        
        //average (25 iterations, ignoring first 5)
        int numCountedIterations = (iterations > 1 ? (iterations-5) : 1);;
        insertRACycles /= numCountedIterations;
        insertFACycles /= numCountedIterations;
        insertTACycles /= numCountedIterations;
        updateACycles /= numCountedIterations;
        selectACycles /= numCountedIterations;
        insertRLCycles /= numCountedIterations;
        insertFLCycles /= numCountedIterations;
        insertTLCycles /= numCountedIterations;
        updateLCycles /= numCountedIterations;
        selectLCycles /= numCountedIterations;
        data += getString(dataSize) + ",";
        data += getString(selectLCycles) + "," + getString(selectACycles) + ",";
        data += getString(insertRLCycles) + "," + getString(insertRACycles) + ",";
        data += getString(insertFLCycles) + "," + getString(insertFACycles) + ",";
        data += getString(insertTLCycles) + "," + getString(insertTACycles) + ",";
        data += getString(updateLCycles) + "," + getString(updateACycles) + "\n";
    }
    
    //Write data to file
    ofstream myfile;
    myfile.open ("/tmp/output.csv");
    myfile << h1 << endl << h2 << endl << data;
    myfile.close();
    
    cout << "Total Cycles :" << (tick() - totalRes) << endl;
    cout << "DONE!" << endl;
    return 0;
}
