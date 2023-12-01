#ifndef WEB_H
#define WEB_H

#include <QObject>
#include <QPainter>


class Web : public QObject {
  Q_OBJECT
 public:
  explicit Web(QObject *parent = nullptr);
     //QRect *windowRect_ = new QRect;
  void DrawWeb(QPainter *painter, QRect windowRect_, QPoint cursorPosition_);



 signals:
};

#endif  // WEB_H
