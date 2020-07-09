#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class PaintScene : public QGraphicsScene
{
  Q_OBJECT
public:
  PaintScene(int id, QObject *parent = nullptr);
  ~PaintScene();
private:
  int id;
  QPointF previousPoint;
  QPointF previousPPoint;

  void mousePressEvent(QGraphicsSceneMouseEvent * event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  QColor currColor;
public slots:
  void drawAt(int id, int x ,int y, bool finish);
signals:
  void sendField(int id, int x, int y, bool finish);
};

#endif // PAINTSCENE_H
