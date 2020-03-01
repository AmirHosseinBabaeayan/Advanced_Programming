
#ifndef Node_H
#define Node_H

#include <string>
#include<QList>
#include<QGraphicsView>
#include <QGraphicsItem>
#define RADIUS 40

class DfaWindow;
class TuringWindow;
class Edge;

class Node: public QGraphicsItem
{
    friend class DfaWindow;
    friend class TuringWindow;
public:
    Node( qreal ,qreal );
    Node();

    void  set_X(qreal x);
    void  set_Y(qreal y);
    qreal get_X(void);
    qreal get_Y(void);
    void setCenterPoint( QPointF );
    QPointF getCenterPoint( void );

    Edge* addEdge(Edge*);
    void deleteEdge(Edge*);
    QList< Edge* > getEdges();

    bool getIsFinalNode();
    void setAsFinalNode();

    void setThisAsInitialNode();
    void unSetThisAsInitialNode();

    void setLable( unsigned int );
    void setLable( std::string );
    std::string getLable();

    void setdisplayed();
    void setHidden();

    static unsigned int getLableCounter();
    static bool getIsInitialNodeHasBeenChoosen();


protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void drawAsFinal( QPainter* );
    void drawInitialNodeStyle( QPainter* );
    void drawAsDisplayed( QPainter* );

private:
    QList<Edge*> edgeList;
    QPointF center;
    bool isFinalNode;
    bool thisIsInitalNode;
    QString nodeLable;
    bool displayNode;

    static bool isInitialNodeHasBeenChoosen;
    static unsigned int counter;
    static QColor color;
};


#endif Node_H

