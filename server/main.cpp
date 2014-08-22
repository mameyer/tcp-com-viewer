#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "TcpServerViewer.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    TcpServerViewer *tcpServerViewer = new TcpServerViewer();
    tcpServerViewer->show();
    
    app.exec();
    
    delete tcpServerViewer;
    
    return EXIT_SUCCESS;
}
