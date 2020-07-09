#include "paintscene.h"
#include <QDebug>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPainter>

PaintScene::PaintScene(int id, QObject *parent) : QGraphicsScene(parent)
{
  this->id = id;
  this->currColor = QColor(0,0,0);
  this->previousPPoint = QPointF(0,0);
}

PaintScene::~PaintScene(){}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//  event->
  previousPoint = event->scenePos();
  addEllipse(event->scenePos().x() - 5,
             event->scenePos().y() - 5,
             10,
             10,
             QPen(Qt::NoPen),
             QBrush(currColor)); //TODO: color
  emit sendField(id, previousPoint.x()-5,previousPoint.y()-5, 0);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  addLine(previousPoint.x(),
          previousPoint.y(),
          event->scenePos().x(),
          event->scenePos().y(),
          QPen(currColor,10,Qt::SolidLine,Qt::RoundCap));
  previousPoint = event->scenePos();
  emit sendField(id, previousPoint.x(),previousPoint.y(), 0);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
  emit sendField(id, previousPoint.x()-5,previousPoint.y()-5, 1);
}

void PaintScene::drawAt(int id, int x, int y, bool finish)
{
  if (id==this->id){
    if(previousPPoint==QPointF(0,0)){
      addEllipse(x,
                 y,
                 10,
                 10,
                 QPen(Qt::NoPen),
                 QBrush(currColor)); //TODO: color
    }else{
      addLine(previousPPoint.x(),
              previousPPoint.y(),
                 x,
                 y,
                 QPen(currColor,10,Qt::SolidLine,Qt::RoundCap));
    }
    if(finish){
      previousPPoint = QPointF(0,0);
    }else{
      previousPPoint = QPointF(x,y);
    }
  }
}
