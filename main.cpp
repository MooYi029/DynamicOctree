#include "DynamicOctreeDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    clock_t start, endt;
    start = clock();
    QApplication a(argc, argv);
    DynamicOctreeDemo w;
    w.show();
    endt = clock();
    std::cout << "程序渲染所需时间 ： " << (double)(endt - start) / CLOCKS_PER_SEC << "s" << std::endl;
    return a.exec();
}
