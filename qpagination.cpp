#include "qpagination.h"

#include <QHBoxLayout>

QPagination::QPagination(QWidget *parent, int height) : QWidget(parent),
    height(height) {

    setMinimumHeight(height);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(6, 0, 6, 0);
    hbox->setSpacing(0);

    currentPage = 0;
}

void QPagination::setTotalPages(int totalPages) {
    this->totalPages = totalPages;
}
