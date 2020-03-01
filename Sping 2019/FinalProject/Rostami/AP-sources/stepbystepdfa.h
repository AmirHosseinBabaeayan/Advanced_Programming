#ifndef STEPBYSTEP_H
#define STEPBYSTEP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QList>
#include "edge.h"
#include "node.h"

class QGraphicsView;

class StepByStepDfa : public QGraphicsView
{
    Q_OBJECT
public:
    StepByStepDfa(QWidget* parent = 0);
    void setNodeListView( QList<Node*> );
    void setEdgeListView( QList<Edge*> );
    void play();
    virtual void next();
    virtual void emptyScene();
    bool getPlaySituation();
public slots:

protected:
    void set_Attribute( Node* ,Node* );
    void drawInitialStyle( Node* );
    virtual void drawEdgeValue( int ,Node* );
    QGraphicsScene* getScene();
private:
    QList<Node*> nodes;
    QList<Edge*> edges;
    QGraphicsScene* scene;
    Node* prevNode;
    bool played;
    int length;
    int index;
    int nodeStepCounter;
};

#endif // STEPBYSTEP_H
