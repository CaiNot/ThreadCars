#include "data.h"
#include <iostream>

int main() {

    for (uint8_t i = 0; i < 4; i++) {
//        thread t(output, i);
        //t.join(); 使用join表示子线程结束之后再运行主线程
//        t.detach();
    }

    Route wR(W), sR(S), eR(E), nR(N);

    thread workThread(cainot::work);

    thread waitThreadW(cainot::ready, wR), waitThreadS(cainot::ready, sR),
            waitThreadE(cainot::ready, eR), waitThreadN(cainot::ready, nR);

    getchar();
    /**
     * 如果main结束了，子线程也会结束，所以，强行不结束。
    **/
    return 0;
}