#include "qpagination.h"

#include <QDebug>
#include <QPainter>
#include <QStyleOption>

QPagination::QPagination(QWidget *parent, int height) : QWidget(parent),
    height(height) {

    buttonPrevious = nullptr;
    buttonNext = nullptr;
//    buttons = QVector<QPushButton>();

    setMinimumHeight(height);

    currentPage = 1;
    previousPage = -1;
}

QPagination::~QPagination() {
    delete buttonNext;
    delete buttonPrevious;
}

void QPagination::setTotalPages(int totalPages) {
    this->totalPages = totalPages;
    currentPage = 1;
}

void QPagination::show() {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 0, 6, 0);
    layout->setSpacing(0);

    buttonPrevious = new QPushButton("<", this);
    buttonPrevious->setMinimumSize(24, 24);
    buttonPrevious->setEnabled(false);
    buttonPrevious->setVisible(false);
    connect(buttonPrevious, &QPushButton::clicked, [&](){
        if (currentPage <= 1) {
            return;
        }

        previousPage = currentPage;
        currentPage -= 1;
        onClick();
    });

    buttonNext = new QPushButton(">", this);
    buttonNext->setMinimumSize(24, 24);
    buttonNext->setEnabled(false);
    buttonNext->setVisible(false);
    connect(buttonNext, &QPushButton::clicked, [&]() {
        if (currentPage >= totalPages) {
            return;
        }

        previousPage = currentPage;
        currentPage += 1;
        onClick();
    });

    if (totalPages > 1) {
        buttonPrevious->setVisible(true);
        layout->addWidget(buttonPrevious);
    }

    for (int i = 0; i < totalPages; i++) {
        int pageNumber = i + 1;
        QPushButton *button = new QPushButton(QString::number(pageNumber), this);
        button->setMinimumSize(24, 24);
        button->setStyleSheet("QPushButton:hover { background:transparent; }");

        if (currentPage == pageNumber) {
            button->setEnabled(false);
        }

        connect(button, &QPushButton::clicked, [=]() {
            previousPage = currentPage;
            currentPage = pageNumber;
            onClick();
        });
        layout->addWidget(button);
        buttons.append(button);
    }

    if (totalPages > 1) {
        buttonNext->setVisible(true);
        buttonNext->setEnabled(true);
        layout->addWidget(buttonNext);
    }
}

void QPagination::onClick() {
    buttonPrevious->setEnabled(currentPage > 1);

    buttonNext->setEnabled(currentPage < totalPages);

    buttons.at(previousPage - 1)->setEnabled(true);
    buttons.at(currentPage - 1)->setEnabled(false);

    emit onPageChange(currentPage);
}

void QPagination::paintEvent(QPaintEvent *) {
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
