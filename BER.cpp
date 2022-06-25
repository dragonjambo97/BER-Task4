#include <tuple>
#include <iostream>
#include <chrono>
#include <fstream>
#include <bitset>
using namespace std;

tuple<int, int, float, long> makeComparison(fstream &file_A, fstream &file_B){

    int roznica = 0, porownanie = 0;
    long sizeInBytes = 0L;
    float ber = 0.;
    char a, b;
    string bitSetA, bitSetB;

    createLog("Rozpoczêto analizê.");
    auto start = chrono::high_resolution_clock::now();

    while(!file_A.eof()){

        a = file_A.get();
        b = file_B.get();
        sizeInBytes++;

        if(a != b){
            bitSetA = bitset<8>(a).to_string();
            bitSetB = bitset<8>(b).to_string();

            for(int i = 7; i >= 0; i--){
                if(bitSetA[i] != bitSetB[i]) diff++;
                porownanie++;
            }
        }
    }

    sizeInBytes -= 1;
    ber = float(roznica) / (sizeInBytes * 8.) * 100.;

    auto stop = chrono::high_resolution_clock::now();
    createLog("Zakoñczono.");
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    tuple<int, int, float, long> results = make_tuple(porownanie, roznica, ber, duration.count());
    return results;
}

