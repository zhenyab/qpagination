#include "qpagination.h"

#include <QDebug>
#include <QPainter>
#include <QStyleOption>

QPagination::QPagination(QWidget *parent, int height) : QWidget(parent),
    height(height) {

    buttonPrevious = nullptr;
    buttonNext = nullptr;

    setMinimumHeight(height);

    previousPage = -1;
    currentPage = 1;
    totalButtons = 7;
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
        previousPage = currentPage;
        currentPage -= 1;

        calculate();
    });

    buttonNext = new QPushButton(">", this);
    buttonNext->setMinimumSize(24, 24);
    buttonNext->setEnabled(false);
    buttonNext->setVisible(false);
    connect(buttonNext, &QPushButton::clicked, [&]() {
        previousPage = currentPage;
        currentPage += 1;

        calculate();
    });

    if (totalPages > 1) {
        buttonPrevious->setVisible(true);
        layout->addWidget(buttonPrevious);
    }

    if (totalButtons > totalPages) {
        totalButtons = totalPages;
    }

    for (int i = 0; i < totalButtons; i++) {
        QPushButton *button = new QPushButton(this);
        button->setMinimumSize(24, 24);
        button->setStyleSheet("QPushButton:hover { background:transparent; }");

        int pageNumber = -1;
        if (totalPages > totalButtons + 1) {
            if (i == 0) {
                button->setProperty("page", 1);
                pageNumber = 1;
            } else if (i == totalButtons - 1) {
                button->setProperty("page", totalPages);
                pageNumber = totalPages;
            } else {
                if (i <= 4) {
                    pageNumber = i + 1;
                }
            }
        } else {
            pageNumber = i + 1;
        }

        button->setProperty("page", pageNumber);
        if (pageNumber > 0) {
            button->setText(QString::number(pageNumber));
        } else {
            button->setText("...");
        }

        connect(button, &QPushButton::clicked, [this, button]() {
            QVariant variant = button->property("page");
            int pageNumber = variant.toInt();
            int newCurrentPage = currentPage;

            if (pageNumber > 0) {
                newCurrentPage = pageNumber;
            } else if (pageNumber == -1) {
                newCurrentPage = currentPage + 3;
            } else if (pageNumber == -2) {
                newCurrentPage = currentPage - 3;
            }

            if (newCurrentPage < 1) {
                newCurrentPage = 1;
            } else if (newCurrentPage > totalPages) {
                newCurrentPage = totalPages;
            }

            previousPage = currentPage;
            currentPage = newCurrentPage;

            calculate();
        });
        layout->addWidget(button);
        buttons.append(button);
    }

    if (totalPages > 1) {
        buttonNext->setVisible(true);
        buttonNext->setEnabled(true);
        layout->addWidget(buttonNext);
    }

    calculate();
}

void QPagination::calculate() {

    if (totalPages > totalButtons) {
        bool button1 = false;
        bool button5 = false;
        if (currentPage - 1 > 3) {
            button1 = true;
            setButton(1, -2);
        } else {
            setButton(1, 2);
            setButton(2, 3);
            setButton(3, 4);
            setButton(4, 5);
        }

        if (totalPages - currentPage > 3) {
            button5 = true;
            setButton(5, -1);
        } else {
            setButton(2, totalPages - 4);
            setButton(3, totalPages - 3);
            setButton(4, totalPages - 2);
            setButton(5, totalPages - 1);
        }

        if (button1 && button5) {
            setButton(2, currentPage - 1);
            setButton(3, currentPage);
            setButton(4, currentPage + 1);
        }
    }

    for (QPushButton *button : buttons) {
        int page = button->property("page").toInt();
        if (currentPage == page) {
            button->setEnabled(false);
        } else {
            button->setEnabled(true);
        }
    }

    buttonPrevious->setEnabled(currentPage > 1);
    buttonNext->setEnabled(currentPage < totalPages);

    emit onPageChange(currentPage);
}

void QPagination::paintEvent(QPaintEvent *) {
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}

void QPagination::setButton(int index, int pageNumber) {

    QString text;
    if (pageNumber > 0) {
        text = QString::number(pageNumber);
    } else {
        text = "...";
    }

    QPushButton *button = buttons.at(index);
    button->setProperty("page", pageNumber);
    button->setText(text);
}
