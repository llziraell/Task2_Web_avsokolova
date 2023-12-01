#include "widget.h"

#include <QDateTime>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <web.h>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    isDrawingWeb_ = false;

    ellipseMoveTimer_ = new QTimer(this);
    AddToTimerInterval(1000);

//    int positionYDivider = 2;
//    //windowRect_ = rect();
//    ellipsePosition_ =
//        QPoint(windowRect_.x(), windowRect_.height() / positionYDivider);

    // Cоединяем сигнал таймера о том, что время (интервал) прошло со слотом
    // вывода сообщения
    connect(ellipseMoveTimer_, &QTimer::timeout, this, &Widget::ShowMessage);

    // Cоединяем сигнал таймера о том, что время (интервал) прошло со слотом
    // изменения позиции фигуры
    connect(ellipseMoveTimer_, &QTimer::timeout, this,
            &Widget::UpdateEllipsePosition);
}

Widget::~Widget() {}

void Widget::ShowMessage() { qDebug() << QDateTime::currentDateTime(); }

void Widget::UpdateEllipsePosition() {
    int dx = 10;

    ellipsePosition_.setX(ellipsePosition_.x() + dx);

    repaint();  // Принудительно вызываем событие отрисовки
}

void Widget::keyPressEvent(QKeyEvent *event) {
    int deltaTimerInterval = 50;

    if (event->key() == Qt::Key_Space &&
        event->modifiers() == Qt::ControlModifier) {
        ellipseMoveTimer_->start();
    } else if (event->key() == Qt::Key_Left) {
        AddToTimerInterval(deltaTimerInterval);
    } else if (event->key() == Qt::Key_Right) {
        AddToTimerInterval(-deltaTimerInterval);
    }
}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {

        cursorPosition_ = event->pos();
        isDrawingWeb_ = true;
        ShowMousePosition();

        setCursor(Qt::PointingHandCursor);
        repaint();  // Принудительно вызываем событие отрисовки
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawingWeb_) {

        cursorPosition_ = (event->pos());

        int minX = 0;
        int maxX = width();
        int minY = 0;
        int maxY = height();

        if (cursorPosition_.x() < minX) {
            cursorPosition_.setX(minX);
        } else if (cursorPosition_.x() > maxX) {
            cursorPosition_.setX(maxX);
        }

        if (cursorPosition_.y() < minY) {
            cursorPosition_.setY(minY);
        } else if (cursorPosition_.y() > maxY) {
            cursorPosition_.setY(maxY);
        }
        ShowMousePosition();
             repaint();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)  // Убираем сообщение о неиспользуемой переменной event
    isDrawingWeb_ = false;


    unsetCursor();  // Как только заканчиваем рисовать паутину, меняем курсор на
        // стандартный
    //QPainter painter(this);


}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Создаем экземпляр класса для низкоуровневого рисования
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Добавляем сглаживание

    if (isDrawingWeb_) {  // Рисуем паутину и паука при зажатой левой кнопке мыши
             Web *web = new Web;
        web->DrawWeb(&painter,windowRect_ , cursorPosition_);
//        DrawSpider(&painter);
    } else {
         painter.eraseRect(rect());
    }

    if (ellipseMoveTimer_->isActive()) {
        DrawEllipse(&painter);
    }

    // Для очистки отрисованной области
//     painter.eraseRect(rect());
}

void Widget::DrawSpider(QPainter *painter) {
    int width = 5;
    int height = 5;

    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter->drawEllipse(cursorPosition_, width, height);
}

void Widget::DrawEllipse(QPainter *painter) {
    int width = 20;
    int height = 20;

    painter->setBrush(QBrush(Qt::green));
    painter->drawEllipse(ellipsePosition_, width, height);
}

void Widget::ShowMousePosition() {
    // Выводим положение мыши в заголовок окна
    setWindowTitle(
        QString("x: %1; y: %2;")
            .arg(cursorPosition_.x())  // аргумент подставляется вместо %1
            .arg(cursorPosition_.y()));  // аргумент подставляется вместо %2
}

void Widget::AddToTimerInterval(int milliseconds) {
    int minInterval = 100;
    int maxInterval = 1000;

    // Добавляем к текущему интервалу мс для дальнейшей проверки
    int newInterval = ellipseMoveTimer_->interval() + milliseconds;

    // Не даем выйти значению интерваля за указанные границы [minInterval,
    // maxInterval]
    newInterval = qBound(minInterval, newInterval, maxInterval);

    ellipseMoveTimer_->setInterval(newInterval);
}


