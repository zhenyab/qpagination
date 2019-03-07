# Pagination
 a paging widget based on Qt

### Usage Demo
``` c++
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

pagination->setTotalPages(5);
pagination->show();
```
