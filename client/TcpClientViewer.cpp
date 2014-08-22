#include "TcpClientViewer.hpp"

#include <iostream>

TcpClientViewer::TcpClientViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClientViewer())
{
    ui->setupUi(this);
    this->client = NULL;
    QObject::connect(ui->srv_addr_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_addr(QString)));
    QObject::connect(ui->srv_port_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_port(QString)));
    QObject::connect(ui->client_msg_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_client_msg(QString)));
    QObject::connect(ui->actionBeenden,SIGNAL(triggered()),this,SLOT(exit()));
    QObject::connect(ui->server_conn_btn,SIGNAL(clicked()),this,SLOT(run()));
    QObject::connect(ui->send_btn,SIGNAL(clicked()),this,SLOT(send()));
    
    this->ui->send_btn->setDisabled(true);
}

void
TcpClientViewer::attach_server_msg(const QString& server_msg)
{
    std::cout << "attach_server_msg(" << server_msg.toStdString() << ")" << std::endl;
}

void
TcpClientViewer::set_client_msg(const QString& client_msg)
{
    std::cout << "set_client_msg(" << client_msg.toStdString() << ")" << std::endl;
    this->client_msg = client_msg.toStdString();
}

void
TcpClientViewer::set_server_addr(const QString& server_addr)
{
    std::cout << "set_server_addr(" << server_addr.toStdString() << ")" << std::endl;
    this->server_addr = server_addr.toStdString();
}

void
TcpClientViewer::set_server_port(const QString& server_port)
{
    std::cout << "set_server_port(" << server_port.toStdString() << ")" << std::endl;
    this->server_port = server_port.toInt();
}

void TcpClientViewer::exit()
{
    std::cout << "exit()" << std::endl;
    this->close();
}

void TcpClientViewer::run()
{
    std::cout << "run()" << std::endl;

    if (this->client == NULL) {
        if (!this->server_addr.empty() && this->server_port>0) {
            this->client = new TCPClient(this->server_addr, this->server_port);
            this->ui->server_conn_btn->setText("disconnect");
            this->ui->srv_addr_in->setDisabled(true);
            this->ui->srv_port_in->setDisabled(true);
            this->ui->send_btn->setDisabled(false);
        }
    } else {
        this->client->~TCPClient();
        this->client = NULL;
        this->ui->server_conn_btn->setText("connect");
        this->ui->srv_addr_in->setDisabled(false);
        this->ui->srv_port_in->setDisabled(false);
        this->ui->send_btn->setDisabled(true);
    }
}

void TcpClientViewer::send()
{
    std::cout << "send(" << this->client_msg << ")" << std::endl;
    if (!this->client_msg.empty() && this->client != NULL) {
        this->client->send_data(this->client_msg);
    }
}