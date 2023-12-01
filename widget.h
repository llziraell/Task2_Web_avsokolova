#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  private slots:
  void ShowMessage();
  void UpdateEllipsePosition();

  protected:
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void paintEvent(QPaintEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);

  private:
  void DrawWeb(QPainter *painter);
  void DrawEllipse(QPainter *painter);
  void AddToTimerInterval(int milliseconds);
  void DrawSpider(QPainter *painter);
  void ShowMousePosition();

  private:
  QTimer *ellipseMoveTimer_;
  QRect windowRect_;

  QPoint cursorPosition_;
  QPoint ellipsePosition_;

  bool isDrawingWeb_;
  int timeInterval_;
};
#endif  // WIDGET_H
