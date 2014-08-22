#ifndef TCPCLIENTVIEWER_HPP__
#define TCPCLIENTVIEWER_HPP__

#include <QMainWindow>
#include <string>

#include "ui_tcpClientViewer.h"
#include "../../tcp-communication/client/TCPClient.hpp"
#include "../../tcp-communication/common/TCPObserver.hpp"

namespace Ui {
    class TcpClientViewer;
}

class TcpClientViewer : public QMainWindow, public TCPObserver {
    Q_OBJECT
private:
    std::string client_msg;
    std::string server_addr;
    int server_port;
    Ui::TcpClientViewer *ui;
    TCPClient *client;
public:
    TcpClientViewer(QWidget *parent = NULL);
    void register_server_answer();
    void handle_server_disconnect();
public slots:
    void set_client_msg(const QString &);
    void attach_server_msg(const QString &);
    void set_server_addr(const QString &);
    void set_server_port(const QString &);
    void send();
    void exit();
    void run();
};

#endif