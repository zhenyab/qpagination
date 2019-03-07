# Pagination
 a paging widget based on Qt

### Usage Demo
``` c++
QWidget *widget = new QWidget(this);
widget->setGeometry(0, 0, 560, 50);

QHBoxLayout *hbox = new QHBoxLayout(widget);
hbox->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Preferred));

auto qPagination = new QPagination(widget, 30);
hbox->addWidget(qPagination);

QLabel *text = new QLabel(this);
text->setGeometry(120, 50, 40, 20);

connect(qPagination, &QPagination::onPageChange, [=](int currentPage) {
    text->setText(QString::number(currentPage));
});

qPagination->setTotalPages(20);
qPagination->show();
```

![image](https://github.com/daonvshu/Pagination/blob/master/demo.png?raw=true)
