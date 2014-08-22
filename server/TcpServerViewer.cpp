#include "TcpServerViewer.hpp"

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
#include <QtGlobal>

TcpServerViewer::TcpServerViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServerViewer())
{
    ui->setupUi(this);
    this->income_model = new QStringListModel(this);

    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    QObject::connect(ui->run_btn,SIGNAL(clicked()),this,SLOT(run()));
    QObject::connect(ui->port_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_port(const QString &)));
    QObject::connect(ui->srv_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_addr(const QString &)));
    QObject::connect(ui->num_conns_in,SIGNAL(textChanged(const QString &)),this,SLOT(set_server_num_conns(const QString &)));
    this->server = NULL;
    
    this->ui->srv_in->setText(tr("localhost"));
    this->ui->port_in->setText(tr("7777"));
    this->ui->num_conns_in->setText(tr("10"));

    this->ui->income_view->setModel(this->income_model);
}

void
TcpServerViewer::set_val(int val)
{
    if (this->val != val) {
        this->val = val;
        emit this->val_changed(val);
    }
}

void
TcpServerViewer::run()
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
            this->ui->srv_in->setDisabled(true);
            this->ui->port_in->setDisabled(true);
            this->ui->num_conns_in->setDisabled(true);
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
        this->ui->srv_in->setDisabled(false);
        this->ui->port_in->setDisabled(false);
        this->ui->num_conns_in->setDisabled(false);
    }
}

void
TcpServerViewer::exit()
{
    this->close();
}

void
TcpServerViewer::set_server_addr(const QString &server_addr)
{
    this->server_addr = server_addr.toStdString();
    std::cout << "set_server_addr: " << this->server_addr << std::endl;
}

void
TcpServerViewer::set_server_num_conns(const QString &num_conns)
{
    this->server_num_conns = num_conns.toInt();
    std::cout << "set_server_num_conns: " << this->server_num_conns << std::endl;
}

void
TcpServerViewer::set_server_port(const QString &server_port)
{
    this->server_port = server_port.toInt();
    std::cout << "set_server_port: " << this->server_port << std::endl;
}

void
TcpServerViewer::attach_to_server_output(std::string output)
{
    this->ui->srv_out->addItem(new QListWidgetItem(output.c_str()));
    std::cout << "attach_to_server_output(" << output << ")" << std::endl;
}

void
TcpServerViewer::update_messages() {
    std::cout << "update_messages()" << std::endl;
    if (this->server != NULL) {
        std::string msg = this->server->next_srv_msg();
        this->attach_to_server_output(msg);
    }
}

void
TcpServerViewer::update_income() {
    std::cout << "update_income()" << std::endl;

    std::pair<int, std::string> in = this->server->next_income();
    std::string income = in.second;

    if (!income.empty()) {
        QString qin = tr(income.c_str());
        if (this->server != NULL && !qin.isEmpty()) {
            this->income_model->insertRow(this->income_model->rowCount());
            QModelIndex index = this->income_model->index(this->income_model->rowCount()-1);
            this->income_model->setData(index, qin);
        }
    }
}

void TcpServerViewer::add_conn()
{
    std::stringstream ss;
    ss << this->server->last_conn_added;
    std::cout << "add_conn(" << ss.str() << ")" << std::endl;
    this->ui->open_conns_out->addItem(new QListWidgetItem(ss.str().c_str()));
}

void TcpServerViewer::rm_conn()
{
    int conn_rm = this->server->last_conn_erased;
    std::cout << "rm_conn(" << conn_rm << ")" << std::endl;

    QString conn_str = QString(conn_rm);
    for(int i=0; i<this->ui->open_conns_out->count(); i++) {
        QListWidgetItem *item = this->ui->open_conns_out->takeItem(i);
        if (item->text() == conn_str) {
            this->ui->open_conns_out->removeItemWidget(item);
            break;
        }
    }
}
