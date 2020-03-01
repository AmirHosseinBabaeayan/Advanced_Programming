#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include <QList>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>

class Node;

class Edge:public QGraphicsItem
{
public:
    Edge( Node* ,Node*  );
    Edge();

    Node* getSourceNode() const;
    Node* getDestNode() const;

    std::string getEdgeValue();
    void setEdgeValue( QString );

    void adjust();

    static void setDigitWeigth( qreal );

    void setIsDuplicatedTrue();
    bool getIsDuplicatedFlag();

protected:
    enum Type { Line ,SameLine ,Ellipse ,SameEllipse };
    void drawSolidLine( QPainter* );
    void drawLable( QPainter* ,int );
    void drawDupLine( QPainter* );
    void drawReflectiveEdge( QPainter* );
    void checkForSameEdge();
    void checkForSymmetryEdge();
    QPointF findFractionLinePoint( double ) const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

private:
    Node* sourceNode;
    Node* destNode;
    QPointF sourcePoint;
    QPointF destPoint;
    std::string value;
    qreal arrowSize;
    static qreal digitWeigth;
    bool isDuplicated;
    bool sameEdgeFlag;
    unsigned int checkForSameEdgeCounter;
    int sameLineCounter;
    int sameEllipseCounter;

};




#endif // EDGE_H
