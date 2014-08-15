#include "TcpComViewer.hpp"

#include <iostream>
#include <QListWidgetItem>
#include <QString>
#include <QEvent>
#include <QPushButton>
#include <QAction>
#include <QApplication>
#include <QLineEdit>

TcpComViewer::TcpComViewer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TcpComViewer())
{
    ui->setupUi(this);
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    QObject::connect(ui->run_btn,SIGNAL(clicked()),this,SLOT(run()));
    QObject::connect(ui->port_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_port(const QString &)));
    QObject::connect(ui->srv_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_addr(const QString &)));
    QObject::connect(ui->num_conns_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_num_conns(const QString &)));
}

void
TcpComViewer::set_val(int val)
{
    if (this->val != val) {
        this->val = val;
        emit this->val_changed(val);
    }
}

void
TcpComViewer::run()
{
    std::cout << "balss" << std::endl;
}

void
TcpComViewer::exit()
{
    this->close();
}

void
TcpComViewer::set_server_addr(const QString &server_addr)
{
    std::cout << "set_server_addr" << std::endl;
}

void
TcpComViewer::set_server_num_conns(const QString &numm_conns)
{
    std::cout << "set_server_num_conns" << std::endl;
}

void
TcpComViewer::set_server_port(const QString &server_port)
{
    std::cout << "set_server_port" << std::endl;
}

void
TcpComViewer::set_server_output(std::string output)
{
    this->ui->srv_out->addItem(new QListWidgetItem(output.c_str()));
    std::cout << "test" << std::endl;
}