#include "data.h"
#include <iostream>
#include <windows.h>

using namespace std;

void show(int n) {
    bool ans[n];
    for (int i = 0; i < n; i++) {
        ans[i] = 0;
    }
    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        if (!ans[result[i]]) {
            cout << result[i] << "begin" << endl;
            ans[result[i]] = true;
        } else {
            cout << result[i] << "end" << endl;
        }
    }
}



int main() {



    Route wR(0), sR(1), eR(2), nR(3);

    wR.addVehiclesRandom(231);
    sR.addVehiclesRandom(770);
    eR.addVehiclesRandom(3241);
    nR.addVehiclesRandom(324);

    cout << "初始化完毕" << endl;
//    getchar();
    Route *routes[4] = {&wR, &sR, &eR, &nR};
//    cout << nR.isEnd() << endl;
//    cout << wR.isEnd() << endl;

    thread workThread(cainot::work, routes);
//
    thread waitThreadW(cainot::ready, &wR), waitThreadS(cainot::ready, &sR),
            waitThreadE(cainot::ready, &eR), waitThreadN(cainot::ready, &nR);
//    cainot::ready(&wR);
//    cout << wR.isEnd() << endl;
//    cout << nR.isEnd() << endl;


//    cainot::work(routes);
    waitThreadW.join();
    waitThreadS.join();
    waitThreadE.join();
    waitThreadN.join();

    workThread.join();
    cout << "END!!!!" << endl;
//    show(15);
    /**
     * 如果main结束了，子线程也会结束，所以，强行不结束。
    **/
//    cobegin

//    coend
    return 0;
}