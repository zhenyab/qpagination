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

    auto qPagination = new QPagination(widget, 30);
    hbox->addWidget(qPagination);

    QLabel *text = new QLabel(this);
    text->setGeometry(120, 50, 40, 20);

    connect(qPagination, &QPagination::onPageChange, [=](int value) {
        text->setText(QString::number(value));
    });

    qPagination->setTotalPages(20);
}

MainWindow::~MainWindow() {
    delete ui;
}
