#include "qpagination.h"

#include <QDebug>

QPagination::QPagination(QWidget *parent, int height) : QWidget(parent),
    height(height) {

    setMinimumHeight(height);

    currentIndex = 0;
}

void QPagination::setTotalPages(int totalPages) {
    this->totalPages = totalPages;
    currentIndex = 0;
}

void QPagination::show() {
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(6, 0, 6, 0);
    hbox->setSpacing(0);

    if (totalPages > 1) {
        QPushButton *buttonPrevious = new QPushButton("<", this);
        buttonPrevious->setMinimumSize(24, 24);
        hbox->addWidget(buttonPrevious);
        connect(buttonPrevious, &QPushButton::clicked, [&](){
            if (currentIndex == 0) {
                buttonPrevious->setEnabled(false);
                buttonPrevious->setVisible(false);
                return;
            }
    //            int offset = 1;
    //            if (curBtnIndex - offset == 2 || curBtnIndex - offset == 10) {
    //                offset++;
    //            }
    //            if (!btn[curBtnIndex - offset]->isVisible()) {
    //                offset++;
    //            }
    //            clicked(curBtnIndex - offset);
            emit onPageChange(currentIndex + 1);
        });
    }

    for (int i = 0; i < 13; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setMinimumSize(24, 24);
        hbox->addWidget(buttons[i]);

        if (i != 2 && i != 10) {
            connect(buttons[i], &QPushButton::clicked, [=]() {
                //clicked(i);
                qDebug() << "Clicked button: " << i;
            });
        } else {
            buttons[i]->setStyleSheet(".QPushButton:hover{background:transparent;}");//去掉省略号hover状态
        }
    }

    if (totalPages > 1) {
        QPushButton *buttonNext = new QPushButton(">", this);
        buttonNext->setMinimumSize(24, 24);
        hbox->addWidget(buttonNext);
        connect(buttonNext, &QPushButton::clicked, [&]() {
//                if (totalSize >= 10 && curBtnIndex + 1 > 12) {
//                    return;
//                } else if (totalSize > 2 && totalSize < 10 && curBtnIndex + 1 > totalSize) {
//                    return;
//                } else if (totalSize < 3 && curBtnIndex + 1 > totalSize - 1) {
//                    return;
//                }

//                int offset = 1;
//                if (!btn[curBtnIndex + offset]->isVisible()) {
//                    offset++;
//                }
//                if (curBtnIndex + offset == 2 || curBtnIndex + offset == 10) {
//                    offset++;
//                }
//                clicked(curBtnIndex + offset);
            });
    }
}
