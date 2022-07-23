#include <iostream>
#include <iomanip>
#include <fstream>
#include <service.h>

using namespace std;

service Check;
const int allStationsSize = 12;
string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class station { //обьект включающий в себ€ всю необходимую информацию об остановке
public:
    bool s_wasHere; //логическа€ переменна€, содержаща€ информацию о том, был ли здесь пользователь или нет
    int s_drivingTime; //целочисленна€ переменна€ содержаща€ врем€ в пути по данной дороге
    int s_waitingTime; //переменна€ содержаща€ информацию о том, сколько времени нужно подождать чтобы продолжить движение
    int s_stationNumber; //переменна€ содержаща€ номер данной остановки

private:
    string str1 = "min + (";

public:
    int allTime() { //функци€ отвечающа€ за подсчет времени затраченного на преодоление данной точки
        return s_drivingTime + s_waitingTime;
    }
    bool driveable() { //функци€ предназначенна€ дл€ проверки возможности проезда через данную точку
        if ((s_drivingTime >= 1) and (s_wasHere == false)) {
            return true;
        }
        else {
            return false;
        }
    }
    string output() { //функци€ дл€ вывода информации в консоль
        return " ---> " + to_string(s_drivingTime) + str1 + to_string(s_waitingTime) + "min waiting) ---> ";
    }
};

void checkStation(char& stationName) {
    Check.check_char(stationName);
    while ((static_cast<int>(stationName) < 65) or (static_cast<int>(stationName) >= 65 + allStationsSize)) {
        cout << " try again: ";
        Check.check_char(stationName);
    }
}

void showAllStations(station allStations[allStationsSize][allStationsSize]) {
    cout << " User was in: " << endl;
    cout << "  ";
    for (int i = 0; i < allStationsSize; i++) {
        cout << alph[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < allStationsSize; i++) {
        cout << " " << alph[i] << " ";
        for (int j = 0; j < allStationsSize; j++) {
            if (allStations[i][j].s_wasHere == true) {
                cout << "1 ";
            }
            else if (allStations[i][j].s_wasHere == false) {
                cout << ". ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

int moving(station allStations[allStationsSize][allStationsSize], int startLocation, int allStationsSize, int finalTime, int stationDestinationNumber) {
    int min = 1000000;
    int nextStation = -1;
    bool fastRoute = false;
    for (int i = 0; i < allStationsSize; i++) {
        if ((allStations[i][startLocation].driveable()) and (i == stationDestinationNumber)) {
            cout << " " << alph[startLocation] << allStations[i][startLocation].output() << alph[i] << endl;
            finalTime += allStations[i][startLocation].allTime();
            return finalTime;
        }
    }
    for (int i = 0; i < allStationsSize; i++) { //основной цикл
        if (allStations[i][startLocation].driveable()) {
            for (int k = 0; k < allStationsSize; k++) { //внутренний цикл позвол€ющий проверить следующую станцию после выбранной
                if ((k != startLocation) and (allStations[i][startLocation].allTime() < min) and (allStations[i][k].driveable())) { //проверка на выгодность
                    min = allStations[i][startLocation].allTime();
                    nextStation = i;
                }
                if ((k == stationDestinationNumber) and (allStations[i][k].driveable())) { //проверка на быстрое завершение алгоритма
                    nextStation = i;
                    fastRoute = true;
                    break;
                }
            }
            if (fastRoute) {
                break;
            }
        }
    }
    if (nextStation == -1) {
        cout << " Unavailable route" << endl;
        return finalTime;
    }
    cout << " " << alph[startLocation] << allStations[nextStation][startLocation].output() << alph[nextStation] << endl;
    finalTime += allStations[nextStation][startLocation].allTime();
    for (int i = 0; i < allStationsSize; i++) { //цикл записывающий посещЄнные станции в статус посещЄнных
        for (int j = 0; j < allStationsSize; j++) {
            if ((i == startLocation) or (j == startLocation)) {
                allStations[j][i].s_wasHere = true;
            }
        }
    }
    //showAllStations(allStations);
    moving(allStations, nextStation, allStationsSize, finalTime, stationDestinationNumber); //запуск этой же функции заново
}

void mainProgram(station allStations[allStationsSize][allStationsSize]) {
    while (Check.continuation()) {
        ifstream buses_file("C:\\vs_files\\buses_file_2.0.txt");
        char stationLocationName;
        char stationDestinationName;
        string stringRange;
        int finalTime = 0;
        int endTime = 0;
        int stationLocationNumber;
        int stationDestinationNumber;

        //showAllStations(allStations);

        for (int i = 0; i < allStationsSize; i++) {
            for (int j = 0; j < allStationsSize; j++) {
                allStations[i][j].s_wasHere = false;
                allStations[j][i].s_wasHere = false;
            }
        }

        //showAllStations(allStations);

        cout << " Please type station name: ";
        checkStation(stationLocationName);
        stationLocationNumber = alph.find(stationLocationName);

        cout << " Please type destination station name: ";
        checkStation(stationDestinationName);
        stationDestinationNumber = alph.find(stationDestinationName);
        while (stationDestinationNumber == stationLocationNumber) {
            cout << " try again: ";
            checkStation(stationDestinationName);
            stationDestinationNumber = alph.find(stationDestinationName);
        }

        cout << endl << " Your route: " << endl;
        endTime = moving(allStations, stationLocationNumber, allStationsSize, finalTime, stationDestinationNumber);
        cout << " Final time: ";
        if (endTime / 60 >= 2) {
            cout << endTime / 60 << " hours " << endTime % 60 << " minutes " << endl;
        }
        else if (endTime / 60 == 1) {
            cout << endTime / 60 << " hour " << endTime % 60 << " minutes " << endl;
        }
        else {
            cout << endTime << " minutes " << endl;
        }
        cout << " Show routes? (y/n):";
        char variant;
        cin >> variant;
        if (variant == 'y') {
            showAllStations(allStations);
        }
        else if (variant == 'n') {
            cout << " End of program" << endl;
        }
        else {
            cout << " Please type choose 'y' or 'n' " << endl;
        }
    }
}

int main() {
    int var;
    while (true) {
        ifstream buses_file("C:\\vs_files\\buses_file_2.0.txt");
        string stationLocationName;
        string stationDestinationName;
        string stringRange;
        int finalTime = 0;
        int stationLocationNumber;
        int stationDestinationNumber;
        int waitingTime;
        station allStations[allStationsSize][allStationsSize];
        int i = 0;

        for (int i = 0; i < allStationsSize; i++) {
            for (int j = 0; j < allStationsSize; j++) {
                buses_file >> stringRange;
                if (stringRange == ".") {
                    allStations[i][j].s_drivingTime = -1;
                }
                else {
                    allStations[i][j].s_drivingTime = stoi(stringRange);
                    allStations[i][j].s_stationNumber = i;
                }
                allStations[i][j].s_wasHere = false;
                allStations[j][i].s_wasHere = false;
            }
        }

        for (int i = 0; i < allStationsSize; i++) {
            buses_file >> stationLocationName >> waitingTime;
            for (int j = 0; j < allStationsSize; j++) {
                allStations[j][i].s_waitingTime = waitingTime;
            }
        }

        cout << " Starting: " << endl;
        cout << " 1 - Main Program" << endl;
        cout << " 2 - Show Routes" << endl;
        cout << " 0 - Close Program" << endl;
        cout << " Choose variant: ";

        Check.check_int(var);
        if (var == 1) {
            mainProgram(allStations);
        }
        else if (var == 2) {
            showAllStations(allStations);
        }
        else if (var == 0) {
            break;
        }
        else {
            cout << " try again" << endl;
        }
    }
}