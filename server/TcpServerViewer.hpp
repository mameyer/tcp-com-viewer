#ifndef TCPSERVERVIEWER_HPP__
#define TCPSERVERVIEWER_HPP__

#include <QMainWindow>
#include <QAbstractListModel>
#include <QtCore>
#include <QtGui>

#include "ui_tcpServerViewer.h"
#include "../../tcp-communication/server/TCPServer.hpp"
#include "../../tcp-communication/common/Observer.hpp"

namespace Ui {
    class TcpServerViewer;
}

class TcpServerViewer : public QMainWindow, public Observer
{
    Q_OBJECT
private:
    int val;
    Ui::TcpServerViewer *ui;
    TCPServer *server;
    std::string server_addr;
    int server_port;
    int server_num_conns;
    QStringListModel *income_model;
public:
    TcpServerViewer(QWidget *parent = NULL);
    int get_val() const {
        return val;
    }
    void update_messages();
    void update_income();
    void add_conn();
    void rm_conn();
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