/**
 * @author Eugene Bogomolny
 *
 */
#ifndef QPAGINATION_H
#define QPAGINATION_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class QPagination : public QWidget {
    Q_OBJECT
public:
    explicit QPagination(QWidget *parent = nullptr, int height = 30);

    /**
     * After all settings for the widget have been done, need to call this method once
     *
     * @brief show
     */
    void show();

    /**
     * Set total pages to show in the widget.
     * Can be dinamically reset to new number, and widget will redraw it accordingly.
     * In this case the current page will reset to 1
     *
     * @brief setTotalPages
     * @param totalPages
     */
    void setTotalPages(int totalPages);

    /**
     * Optional.
     * Set buttons size. Default value is 24 x 24
     *
     * @brief setButtonsSize
     * @param width
     * @param height
     */
    void setButtonsSize(int width, int height);

    /**
     * Set custom text or icon with tooltip for previous button
     *
     * @brief setPreviousButton
     * @param text
     * @param icon
     */
    void setPreviousButton(const QPixmap &icon, const QString &text);

    /**
     * Set custom text or icon with tooltip for next button
     *
     * @brief setPreviousButton
     * @param text
     * @param icon
     */
    void setNextButton(const QPixmap &icon, const QString &text);

signals:
    void onPageChange(int currentPage);

public slots:

protected:
    void paintEvent(QPaintEvent*) override;

private:
    int height;
    int totalPages;
    int previousPage;
    int currentPage;
    int totalButtons;
    QSize buttonSize;
    QPushButton *buttonPrevious;
    QPushButton *buttonNext;
    QVector<QPushButton*> buttons;

    void calculate();
    void setButton(int index, int pageNumber);
};

#endif // QPAGINATION_H
