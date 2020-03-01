#ifndef GraphView_H
#define GraphView_H

#include "node.h"
#include "edge.h"
#define RADIUS 40
#include <QObject>
#include <QWidget>
#include<QGraphicsView>
#include<QPainter>
#include<iostream>
#include <math.h>

class DfaWindow;
class TuringWindow;

class GraphViewDfa:public QGraphicsView
{
    Q_OBJECT
    friend class DfaWindow;
    friend class TuringWindow;
public:

    GraphViewDfa(QWidget *parent = 0);

    virtual QString setEdgeValueInputDialog();
    QList<Node*> getNodeListView();
    void setSceneRender( QPainter* );
    Node* getInitialNode();

public slots:
    void setAsInitialNodeRequested();
    void setAsFinalNodeRequested();
    void unSetAsInitialNodeRequested();
    void showMessageBox();

protected:
    void mouseReleaseEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressNodeButtonActivated  ( QPointF ,QMouseEvent* );
    void mouseMoveNodeButtonActivated   ( QPointF ,QMouseEvent* );
    void mouseReleaseNodeButtonActivated( QPointF ,QMouseEvent* );

    void mousePressEdgeButtonActivated  ( QPointF ,QMouseEvent* );
    void mouseMoveEdgeButtonActivated   ( QPointF ,QMouseEvent* );
    void mouseReleaseEdgeButtonActivated( QPointF ,QMouseEvent* );

    void mousePressSelectButtonActivated  ( QPointF ,QMouseEvent* );
    void mouseMoveSelectButtonActivated   ( QPointF ,QMouseEvent* );
    void mouseReleaseSelectButtonActivated( QPointF ,QMouseEvent* );

    void mouseReleaseRemoveButtonActivated( QPointF ,QMouseEvent* );

    void checkIsRightClicked  ( QPointF ,QMouseEvent* );

    Node* isInAnyCircle(QPointF);
    Node* isInAnyNode( QPointF);

private:

    static bool edgeButtonActivated;
    static bool nodeButtonActivated;
    static bool selectButtonActivated;
    static bool removeButtonActivated;
    Node* InitialNode;
    QList < Edge* > edgeListView;
    QList < Node* > nodeListView;
    QGraphicsScene* scene;
    Node* pressedNode;
    QGraphicsLineItem* tempLine;
    Node* tempNode;

};

#endif GraphView_H
