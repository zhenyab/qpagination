#ifndef QPAGINATION_H
#define QPAGINATION_H

#include <QWidget>

class QPagination : public QWidget {
    Q_OBJECT
public:
    explicit QPagination(QWidget *parent = nullptr, int height = 30);

    void setTotalPages(int);

signals:
    void onPageChange(int currentPage);

public slots:

private:
    int height;
    int totalPages;
    int currentPage;
};

#endif // QPAGINATION_H
