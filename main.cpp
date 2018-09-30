#include "data.h"
#include <iostream>

using namespace std;

int main() {

    for (uint8_t i = 0; i < 4; i++) {
//        thread t(output, i);
        //t.join(); 使用join表示子线程结束之后再运行主线程
//        t.detach();
    }

    Route wR(W), sR(S), eR(E), nR(N);

    wR.addVehiclesRandom(6);
    sR.addVehiclesRandom(3);
    eR.addVehiclesRandom(2);
    nR.addVehiclesRandom(7);

    cout << "初始化完毕" << endl;
//    getchar();
    Route *routes[4] = {&wR, &sR, &eR, &nR};
//    cout << nR.isEnd() << endl;
//    cout << wR.isEnd() << endl;

    thread workThread(cainot::work, routes);
//
    thread waitThreadW(cainot::ready, &wR), waitThreadS(cainot::ready, &sR),
            waitThreadE(cainot::ready, &eR), waitThreadN(cainot::ready, &nR);
//    cainot::ready(wR);
//    cout << wR.isEnd() << endl;
//    cout << nR.isEnd() << endl;


//    cainot::work(false);
//    workThread.join();
    waitThreadW.join();
    workThread.join();
    cout << "END!!!!" << endl;
    /**
     * 如果main结束了，子线程也会结束，所以，强行不结束。
    **/
    return 0;
}