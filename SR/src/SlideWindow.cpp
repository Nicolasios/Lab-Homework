#include "SlideWindow.h"
#include <iostream>
#include <Global.h>
SlideWindow::SlideWindow(int size) : size(size), vector<Packet>(Configuration::CHACE_SIZE)
{
}

Packet &SlideWindow::operator[](int seq)
{
    return vector<Packet>::operator[](seq % Configuration::CHACE_SIZE);
}

void SlideWindow::ShowWindow(const int base)
{
    for (int i = 0; i < size; i++)
    {
        printf("i:%d\n", i);
        pUtils->printPacket("Packet in the SlideWindow ", this->operator[](i + base));
    }
    printf("*****************************************************\n");
    return;
}

SlideWindow::~SlideWindow() {}