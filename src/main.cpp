#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "TcpComViewer.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    TcpComViewer *tcpComViewer = new TcpComViewer();
    tcpComViewer->show();
    
    app.exec();
    
    delete tcpComViewer;
    
    return EXIT_SUCCESS;
}
