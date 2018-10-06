#include "data.h"
#include <iostream>
#include <windows.h>

using namespace std;

int cainot::leaveCars = 0;

int main() {

    Route wR(0), sR(1), eR(2), nR(3);

    int inputNums[4], sum = 0;

    cout << "备注: 0表示西方向，1表示南方向，2表示东方向，3表示北方向；" << endl;

    for (int i = 0; i < 4; i++) {
        cout << "Please input the num of cars in direction: " << i << endl;
        cin >> inputNums[i];
        sum += inputNums[i];
    }

    cout << "The num of all cars is " << sum << endl;


    wR.addVehiclesRandom(inputNums[0]);
    sR.addVehiclesRandom(inputNums[1]);
    eR.addVehiclesRandom(inputNums[2]);
    nR.addVehiclesRandom(inputNums[3]);

    cout << "初始化完毕" << endl;

    Route *routes[4] = {&wR, &sR, &eR, &nR};


    thread workThread(cainot::work, routes);

    thread waitThreadW(cainot::ready, &wR), waitThreadS(cainot::ready, &sR),
            waitThreadE(cainot::ready, &eR), waitThreadN(cainot::ready, &nR);

    waitThreadW.join();
    waitThreadS.join();
    waitThreadE.join();
    waitThreadN.join();

    workThread.join();

    cout << "END!!!!" << endl;

    cout << "the num of cars that leaved is " << cainot::leaveCars << endl;
    cout << "your input is " << sum << endl;
    return 0;
}