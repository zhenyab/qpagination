#include "mainwindow.h"
#include "qpagination.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto widget = new QWidget(this);
    widget->setGeometry(0, 0, 560, 50);

    auto hbox = new QHBoxLayout(widget);
    hbox->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Preferred));

    QPagination *pagination = new QPagination(widget);
    hbox->addWidget(pagination);

    auto text = new QLabel(this);
    text->setGeometry(120, 50, 40, 20);
    text->setText("1");

    connect(pagination, &QPagination::onPageChange, [=](int value) {
        text->setText(QString::number(value));
    });

    pagination->setTotalPages(20);
    pagination->show();
}

MainWindow::~MainWindow() {
    delete ui;
}
