#include "stepbystepdfa.h"
#include <iostream>
#include <QMessageBox>
#include <QGraphicsScene>

StepByStepDfa::StepByStepDfa(QWidget* parent):QGraphicsView(parent),nodeStepCounter(-1),played(false),length(0),index(0),prevNode(nullptr){
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect( 0, 0, 155, 5000 );
    setScene(scene);
    this->scene = scene;
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    scale(qreal(1), qreal(1));
    centerOn( QPointF(0 , 0) );
//    setMinimumSize(400, 400);
}

void StepByStepDfa::setNodeListView(QList<Node *> nodes){
    if ( nodes.length() != 0 ){
        this->nodes = nodes;
        this->length= nodes.length();
    }
}

void StepByStepDfa::setEdgeListView(QList<Edge *> edges){
    if ( edges.length() != 0 ){
        this->edges = edges;
    }
}

void StepByStepDfa::play(){
    if ( !getPlaySituation() ){
        played = true;
        this->index = length - 1;
        next();
    }
    else {
        QMessageBox::critical( this, "اشتب میزنی", "اجرا شروع شده است دکمه بعدی را بزنید !");
    }
}

bool StepByStepDfa::getPlaySituation(){
    return played;
}

void StepByStepDfa::next(){
    if ( nodeStepCounter != 50 ) nodeStepCounter++;
    else {
        QMessageBox::critical( this ,"اتمام ظرفیت :(" ,"ظرفیت اجرای گام به گام پر شد!..");
        return;
    }
    if ( index == -1 ){
        QMessageBox::critical( this, "اتمام اجرا", "اجرا تمام شد ..." );
        return;
    }
    Node* node = new Node();
    set_Attribute( nodes.at(index) ,node );
    scene->addItem( node );
    scene->addLine(0 ,100 + 100 * nodeStepCounter ,170 ,100 + 100 * nodeStepCounter);
    drawEdgeValue( index ,node );
    scene->update();
    if ( index == length - 1 ) drawInitialStyle( node );
    index--;
}

void StepByStepDfa::drawEdgeValue(int index ,Node* node){
    if ( index == 0 ) return;
    Node* secondNode = new Node( node->get_X() ,node->get_Y() + 70 );
    Edge* edge = new Edge( node ,secondNode );
    edge->setEdgeValue( QString::fromStdString( edges.at( index - 1 )->getEdgeValue() ) );
    scene->addItem( edge );
}

void StepByStepDfa::set_Attribute(Node * nodeItem ,Node * node){
    if ( prevNode ){
        this->prevNode->setHidden();
        prevNode->update();
    }

    if ( nodeItem->getIsFinalNode() ) node->setAsFinalNode();
    node->setLable( nodeItem->getLable() );
    node->setCenterPoint( QPointF(85,50 + 100 * nodeStepCounter) );
    node->setHidden();

    nodeItem->setdisplayed();
    nodeItem->update();
    this->prevNode = nodeItem;
}

void StepByStepDfa::drawInitialStyle(Node * node){
    QPointF first( node->get_X() - RADIUS/2 ,node->get_Y() );
    QPointF second( node->get_X() - RADIUS ,node->get_Y() - RADIUS/2 );
    QPointF third( node->get_X() - RADIUS ,node->get_Y() + RADIUS/2 );
    scene->addPolygon( QPolygonF() << first << second << third );
}

void StepByStepDfa::emptyScene(){
    scene->clear();
    played = false;
    if ( prevNode ){
        prevNode->setHidden();
        prevNode->update();
        prevNode = nullptr;
    }
    nodeStepCounter = -1;
}

QGraphicsScene* StepByStepDfa::getScene(){
    return scene;
}
