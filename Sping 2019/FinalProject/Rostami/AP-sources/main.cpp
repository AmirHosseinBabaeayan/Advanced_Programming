#include <QApplication>
#include<iostream>
#include"graphviewdfa.h"
#include "enterpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnterPage enterpage;
    enterpage.show();
    return a.exec();
}
