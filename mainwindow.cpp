#include "mainwindow.h"
#include "qpagination.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QWidget *widget = new QWidget(this);
    widget->setGeometry(0, 0, 560, 50);

    QHBoxLayout *hbox = new QHBoxLayout(widget);
    hbox->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Preferred));

    QPagination *pagination = new QPagination(widget);
    hbox->addWidget(pagination);

    QLabel *label = new QLabel(this);
    label->setText(QString::number(pagination->getCurrentPage()));

    connect(pagination, &QPagination::onPageChange, [=](int value) {
        label->setText(QString::number(value));
    });

    pagination->setStyleSheet("QPushButton { margin: 0 2px; color: #000; background: #fff; border: 1px solid #f00; border-radius: 5px; } QPushButton:disabled { background: #ccc; } QPushButton:hover { background:transparent; }");
    pagination->setTotalPages(20);
    pagination->show();
}

MainWindow::~MainWindow() {
    delete ui;
}
