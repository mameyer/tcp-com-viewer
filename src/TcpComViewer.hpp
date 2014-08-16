#ifndef TCPCOMVIEWER_HPP__
#define TCPCOMVIEWER_HPP__

#include <QMainWindow>

#include "ui_tcpComViewer.h"
#include "../../tcp-communication/server/TCPServer.hpp"
#include "../../tcp-communication/common/Observer.hpp"

namespace Ui {
    class TcpComViewer;
}

class TcpComViewer : public QMainWindow, public Observer
{
    Q_OBJECT
private:
    int val;
    Ui::TcpComViewer *ui;
    TCPServer *server;
    std::string server_addr;
    int server_port;
    int server_num_conns;
public:
    TcpComViewer(QWidget *parent = NULL);
    int get_val() const {
        return val;
    }
    void update();
public slots:
    void set_val(int);
    void attach_to_server_output(std::string);
    void set_server_port(const QString &);
    void set_server_addr(const QString &);
    void set_server_num_conns(const QString &);
    void run();
    void exit();
signals:
    void val_changed(int);
};

#endif