#include "web.h"

#include <cmath>

Web::Web(QObject *parent) : QObject{parent} {}

void Web::DrawWeb(QPainter *painter, QRect windowRect_, QPoint cursorPosition_) {
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    int halthDivider = 2;

    int numLines = 8;

    QPoint topLeft(windowRect_.topLeft());
    QPoint topRight(windowRect_.topRight());
    QPoint bottomRight(windowRect_.bottomRight());
    QPoint bottomLeft(windowRect_.bottomLeft());
    QPoint halthTop(windowRect_.width() / halthDivider, windowRect_.y());
    QPoint halthBottom(windowRect_.width() / halthDivider, windowRect_.height());
    QPoint halthLeft(windowRect_.x(), windowRect_.height() / halthDivider);
    QPoint halthRight(windowRect_.width(), windowRect_.height() / halthDivider);

    QPoint points[] = {topLeft, halthTop, topRight, halthRight, bottomRight,halthBottom,  bottomLeft,halthLeft, topLeft };

    //исправить цикл!!!
    for (int j = 0; j < numLines; j++){
        painter->drawLine(points[j], cursorPosition_);
        for (float t = 0; t < 1; t+=0.1) {
            QPoint q1(points[j].x() + t*(cursorPosition_.x() - points[j].x()), points[j].y() + t*(cursorPosition_.y()- points[j].y()));
            QPoint q2(points[j+1].x() + t*(cursorPosition_.x() - points[j+1].x()), points[j+1].y() + t*(cursorPosition_.y()- points[j+1].y()));
            painter->drawLine(q1, q2);
        }
    }

    QPoint vector_1 = topLeft - cursorPosition_;
    QPoint vector_2= halthTop - cursorPosition_;

    int dots = QPoint::dotProduct(vector_1, vector_2);
    double length_1 = std::sqrt(vector_1.x() * vector_1.x() + vector_1.y() * vector_1.y());
    double length_2 = std::sqrt(vector_2.x() * vector_2.x() + vector_2.y() * vector_2.y());

    qreal cos_angle = dots / (length_1 * length_2);
    qreal angleRad = std::acos(cos_angle);
    qreal angle = angleRad * 180.0 / M_PI;

    QPointF web_lines[numLines];

    for (int k = 0; k < 15; k++){
        for (int i = 0; i < (numLines); ++i)
        {
            qreal new_angle = angle  * i / numLines;
            qreal x = cursorPosition_.x() + k*cos(new_angle)*60;
            qreal y = cursorPosition_.y() + k*sin(new_angle)*60;
            web_lines[i] = QPointF(x, y);
        }
        painter->drawPolyline(web_lines, numLines);
    }
}

