#include <tuple>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <bitset>
using namespace std;

void createLog(string message){
    fstream logFile;
    logFile.open("log.txt", ios::app);	//tworzenie pliku log
    time_t t = time(0);
    string dt = ctime(&t);
    logFile << endl << dt.substr(0, dt.length()-1) << " : " << message;
    logFile.close();
}

tuple<int, int, float, long> makeComparison(fstream &file_A, fstream &file_B){

    int roznica = 0, porownanie = 0;	
    long sizeInBytes = 0L;
    float ber = 0.;
    char a, b;
    string bitSetA, bitSetB;

    createLog("Rozpoczêto analizê.");	//wpis do pliku log
    auto start = chrono::high_resolution_clock::now(); //rozpoczzêcie pomiaru czasu

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

    auto stop = chrono::high_resolution_clock::now();	//wpis do pliku log //zakonczenie pomiaru czasu
    createLog("Zakoñczono.");
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); //obliczanie czasu 

    tuple<int, int, float, long> results = make_tuple(porownanie, roznica, ber, duration.count());
    return results;
}

int main(int argc, char** argv){
    createLog("_______START_________"); //wpis do pliku log

    if(argc != 3) {
        createLog("Z³a liczba argumentów (" + to_string(argc-1) + ") - potrzebne argumenty: 2."); //wpis do pliku log
        createLog("_______STOP_________");
        return 0;
    }

    fstream file_A, file_B;
    file_A.open(argv[1]);
    file_B.open(argv[2]);
    if(!file_A.is_open() || !file_B.is_open()){
        createLog("Nie mo¿na otworzyæ pliku."); //wpis do pliku log
        createLog("_______STOP_________"); //wpis do pliku log
        return 0;
    } else {
        createLog((string) "Otwarto dwa pliki: (1) " + argv[1] + " (2) " + argv[2]); //wpis do pliku log
    }

    tuple<int, int, float, long> results = makeComparison(file_A, file_B);

    string resultMsg = "Wyniki: Iloœæ porównanych bitów: " + to_string(get<0>(results)) +  //wpis do pliku log
                        "; Ró¿nica w bitach: " + to_string(get<1>(results)) + 
                        "; BER: " + to_string(get<2>(results)) + "%" + 
                        "; Czas: " + to_string(get<3>(results)) + " ms";
    createLog(resultMsg);
    cout << resultMsg << endl;

    file_A.close();
    createLog((string) "Plik " + argv[1] + " zamkniêty."); //wpis do pliku log
    file_B.close();
    createLog((string) "Plik " + argv[2] + " zamkniêty."); //wpis do pliku log

    createLog("_______ STOP_________"); //wpis do pliku log
    return 0;
}

