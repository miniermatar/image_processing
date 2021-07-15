#include "image_proccesing.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Image_Proccesing w;
    w.show();
    return a.exec();
}
