#include "TcpComViewer.hpp"

#include <iostream>
#include <QListWidgetItem>
#include <QString>
#include <QEvent>
#include <QPushButton>
#include <QAction>
#include <QApplication>
#include <QLineEdit>
#include <QMessageBox>
#include <sstream>
#include <QListView>

TcpComViewer::TcpComViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpComViewer())
{
    ui->setupUi(this);
    this->income_model = new QStringListModel(this);
    
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    QObject::connect(ui->run_btn,SIGNAL(clicked()),this,SLOT(run()));
    QObject::connect(ui->port_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_port(const QString &)));
    QObject::connect(ui->srv_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_addr(const QString &)));
    QObject::connect(ui->num_conns_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_num_conns(const QString &)));
    this->server = NULL;
    
    QStringList conns_list;
    conns_list << "test1" << "test2";
    
    this->income_model->setStringList(conns_list);
    this->ui->income_view->setModel(this->income_model);
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
    if (this->server == NULL) {
        if (!this->server_addr.empty() && this->server_port>0) {
            this->server = new TCPServer(this->server_addr, this->server_port);
            this->server->attach(this);
            std::vector<std::string> params;
            std::stringstream ss;
            ss << this->server_num_conns;
            params.push_back(ss.str());
            this->ui->run_btn->setText("stop");
            this->server->run(new Cmd(CMD_RUN, params));
        } else {
            QMessageBox msg;
            msg.critical(0, "Error", "Felder nicht korrekt ausgeüllt!");
            msg.setFixedSize(500,200);
            msg.show();
        }
    } else {
        this->server->stop((void *)0);
        this->server->~TCPServer();
        this->server = NULL;
        this->ui->run_btn->setText("run");
    }
}

void
TcpComViewer::exit()
{
    this->close();
}

void
TcpComViewer::set_server_addr(const QString &server_addr)
{
    this->server_addr = server_addr.toStdString();
    std::cout << "set_server_addr: " << this->server_addr << std::endl;
}

void
TcpComViewer::set_server_num_conns(const QString &num_conns)
{
    this->server_num_conns = num_conns.toInt();
    std::cout << "set_server_num_conns: " << this->server_num_conns << std::endl;
}

void
TcpComViewer::set_server_port(const QString &server_port)
{
    this->server_port = server_port.toInt();
    std::cout << "set_server_port: " << this->server_port << std::endl;
}

void
TcpComViewer::attach_to_server_output(std::string output)
{
    this->ui->srv_out->addItem(new QListWidgetItem(output.c_str()));
    std::cout << "attach_to_server_output(" << output << ")" << std::endl;
}

void
TcpComViewer::update_messages() {
    std::cout << "update_messages()" << std::endl;
    if (this->server != NULL) {
        std::string msg = this->server->next_srv_msg();
        this->attach_to_server_output(msg);
    }
}

void
TcpComViewer::update_income() {
    std::cout << "update_income()" << std::endl;
    
    std::pair<int, std::string> in = this->server->next_income();
    std::string income = in.second;
    
    QString qin = tr(income.c_str());
    if (this->server != NULL) {
        this->income_model->insertRow(this->income_model->rowCount());
        QModelIndex index = this->income_model->index(this->income_model->rowCount()-1);
        this->income_model->setData(index, qin);
    }
}