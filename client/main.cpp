#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "TcpClientViewer.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    TcpClientViewer *tcpClientViewer = new TcpClientViewer();
    tcpClientViewer->show();
    
    app.exec();
    
    delete tcpClientViewer;
    
    return EXIT_SUCCESS;
}
