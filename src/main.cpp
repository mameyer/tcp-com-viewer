#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "TcpComViewer.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    TcpComViewer *tcpComViewer = new TcpComViewer();
    tcpComViewer->show();
    
    for (int i=0; i<10; i++) {
        tcpComViewer->set_server_output("Hallo");
    }
    
    app.exec();
    
    delete tcpComViewer;
    
    return EXIT_SUCCESS;
}
