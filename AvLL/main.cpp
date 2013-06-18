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

static long long res;

int size[5] = {10, 100, 1000, 10000, 100000};


int length (int A[]) {
	return (sizeof(A)/sizeof (int));
}

string getString (long long num) {
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

void print (vector<int> &A, int dataSize) {
	for (int i = 0; i < dataSize; i++) {
		//cout << A[i] << ", ";
    }
	////cout << endl;
}

void doInsert (list<int> &L, int numTimes, int maxSize) {
	if (L.size() >= maxSize) return;
	for (int i = 0; i < numTimes; i++) {
		L.push_front(i);
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

void doInsert (vector<int> &A, int numTimes, int maxSize) {
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
    string h1 = "Size,Selects,,Inserts,,Updates,\n";
    string h2 = ",Linked List ,Array,Linked List,Array,Linked List,Array\n";
    string data = "";
    
    for (int sizeIndex = 0; sizeIndex < 5; sizeIndex++) {
        int dataSize = size[sizeIndex];
        long long updateACycles = 0, insertACycles = 0, selectACycles = 0;
        long long updateLCycles = 0, insertLCycles = 0, selectLCycles = 0;
        for (int s = 0; s<= 29; s++) {
            vector<int> A(dataSize);
            t1 = clock();
            ////cout <<"########### Array ############ "<<endl;
            for  (int i = 1; i < argc-1; i++) {
                if (strcmp("-ni", argv[i]) == 0) {
                    res = tick();
                    doInsert(A, atoi(argv[i+1]), dataSize);
                    if (s > 4) {
                        //ignore first 5 iterations
                        insertACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nu", argv[i]) == 0) {
                    res = tick();
                    doUpdate(A, atoi(argv[i+1]), dataSize);
                    if (s > 4) {
                        //ignore first 5 iterations
                        updateACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-ns", argv[i]) == 0) {
                    res = tick();
                    doSelect(A, atoi(argv[i+1]), dataSize);
                    if (s > 4) {
                        //ignore first 5 iterations
                        selectACycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                }
            }
            ////cout <<"###########" << endl;
            t2 = clock();
            if (s > 4) {
                //ignore the first 5 iterations;
                
            }
        }
        for (int s = 0; s<= 29; s++) {
            list <int> L;
            t1 = clock();
            ////cout <<"######### LinkedList ############ "<<endl;
            for  (int i = 3; i < argc-1; i++) {
                if (strcmp("-ni", argv[i]) == 0) {
                    res = tick();
                    doRandomInsert(L, atoi(argv[i+1]), dataSize);
                    if (s > 4) {
                        //ignore first 5 iterations
                        insertLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-nu", argv[i]) == 0) {
                    res = tick();
                    doUpdate(L, atoi(argv[i+1]));
                    if (s > 4) {
                        //ignore first 5 iterations
                        updateLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                } else if (strcmp("-ns", argv[i]) == 0) {
                    res = tick();
                    doSelect(L, atoi(argv[i+1]));
                    if (s > 4) {
                        //ignore first 5 iterations
                        selectLCycles += (tick() - res);
                    }
                    //cout << "Cycles :" << (tick() - res) << endl;
                }
            }
            ////cout <<"###########" << endl;
            t2 = clock();
            
        }
        
        
        //average (25 iterations, ignoring first 5)
        insertACycles /= 25;
        updateACycles /= 25;
        selectACycles /= 25;
        insertLCycles /= 25;
        updateLCycles /= 25;
        selectLCycles /= 25;
        data += getString(dataSize) + "," + getString(selectLCycles) + "," + getString(selectACycles) + ",";
        data += getString(insertLCycles) + "," + getString(insertACycles) + ",";
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

