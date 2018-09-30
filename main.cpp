#include "data.h"
#include <iostream>

using namespace std;

int main() {

    for (uint8_t i = 0; i < 4; i++) {
//        thread t(output, i);
        //t.join(); ʹ��join��ʾ���߳̽���֮�����������߳�
//        t.detach();
    }

    Route wR(W), sR(S), eR(E), nR(N);

    wR.addVehiclesRandom(6);
    sR.addVehiclesRandom(3);
    eR.addVehiclesRandom(2);
    nR.addVehiclesRandom(7);

    cout << "��ʼ�����" << endl;
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
     * ���main�����ˣ����߳�Ҳ����������ԣ�ǿ�в�������
    **/
    return 0;
}