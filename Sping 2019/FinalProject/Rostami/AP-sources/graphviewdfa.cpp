#include "graphviewdfa.h"
#include"node.h"
#include "edge.h"
#include<iostream>
#include <QWidget>
#include <QInputDialog>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QMessageBox>

bool GraphViewDfa::edgeButtonActivated    = false;
bool GraphViewDfa::nodeButtonActivated    = false;
bool GraphViewDfa::selectButtonActivated  = false;
bool GraphViewDfa::removeButtonActivated  = false;

GraphViewDfa::GraphViewDfa(QWidget* parent):QGraphicsView (parent)
  , pressedNode(nullptr),tempLine( nullptr ),tempNode(nullptr),InitialNode( nullptr ) {
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect( 0 ,0 ,400 ,400 );
    setScene(scene);
    this->scene = scene;
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    scale(qreal(0.9), qreal(0.9));
    setMinimumSize(400, 400);
}

Node * GraphViewDfa::isInAnyCircle(QPointF point){
    const QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if( Node * node = qgraphicsitem_cast<Node*>(item) ){
            qreal xc = node->get_X();
            qreal yc = node->get_Y();
            qreal xp = point.x();
            qreal yp = point.y();
            if(sqrt(pow(xc-xp,2)+pow(yc-yp,2)) < RADIUS/2 ){
                return node;
            }

        }
    }
    return nullptr;

}

Node* GraphViewDfa::isInAnyNode(QPointF point ){
    const QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if( Node* node = qgraphicsitem_cast<Node*>(item) ){
            qreal xc = node->get_X() ;
            qreal yc= node->get_Y() ;
            qreal xp = point.x();
            qreal yp = point.y();
            if(sqrt(pow(xc - xp,2)+pow(yc - yp,2)) < RADIUS ){
                return node;
            }

        }
    }
    return nullptr;
}

void GraphViewDfa::mousePressEvent(QMouseEvent *event){
    QPointF scenePt = mapToScene(event->pos());

    checkIsRightClicked( scenePt ,event );
    if ( GraphViewDfa::nodeButtonActivated ) mousePressNodeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::edgeButtonActivated  ) mousePressEdgeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::selectButtonActivated ) mousePressSelectButtonActivated ( scenePt ,event );

    scene->update();
}

void GraphViewDfa::mousePressNodeButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    if(event->buttons() == Qt::LeftButton){
        tempNode = new Node( cursorCoordinate.x() ,cursorCoordinate.y() );
        scene->addItem( tempNode );
    }
}

void GraphViewDfa::mousePressEdgeButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    if ( Node* node = isInAnyCircle( cursorCoordinate ) ){
        pressedNode = node;
    }

}

void GraphViewDfa::mousePressSelectButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    if ( Node* node = isInAnyCircle( cursorCoordinate ) ){
        pressedNode = node;
    }
}

void GraphViewDfa::checkIsRightClicked(QPointF cursorCoordinate, QMouseEvent* event ){
    if (event->buttons() == Qt::RightButton) {
        if ( pressedNode = isInAnyCircle( cursorCoordinate ) ){

            GraphViewDfa::nodeButtonActivated    = false;
            GraphViewDfa::edgeButtonActivated    = false;
            GraphViewDfa::selectButtonActivated  = false;
            GraphViewDfa::removeButtonActivated  = false;

            QMenu *menu = new QMenu( this );

            QAction* SetAsInitial = new QAction("Set As Initial", this);
            SetAsInitial->setCheckable(true);
            SetAsInitial->setChecked( InitialNode ? true : false );

            if ( !InitialNode ) connect(SetAsInitial, SIGNAL(triggered()), this, SLOT(setAsInitialNodeRequested()));
            else if ( InitialNode == pressedNode ) connect(SetAsInitial, SIGNAL(triggered()), this, SLOT(unSetAsInitialNodeRequested()));
            else connect(SetAsInitial, SIGNAL(triggered()), this, SLOT(showMessageBox()));


            QAction* SetAsFinal = new QAction("Set As Final", this);
            SetAsFinal->setCheckable(true);
            SetAsFinal->setChecked( pressedNode->getIsFinalNode() );
            connect(SetAsFinal, SIGNAL(triggered()), this, SLOT(setAsFinalNodeRequested()));

            menu->addAction(SetAsInitial);
            menu->addAction(SetAsFinal);

            menu->exec( mapToGlobal( event->pos() ) );

        }
    }
}

void GraphViewDfa::showMessageBox(){
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowModality(Qt::ApplicationModal);
    msgBox->setInformativeText("راسی که کلیک شده است راس اولیه نیست!");
    msgBox->setIconPixmap( QPixmap( ":/img/img/Delete.png" ).scaled( 100, 100 ) );
    msgBox->exec();
}

void GraphViewDfa::unSetAsInitialNodeRequested(){
    pressedNode->unSetThisAsInitialNode();
    pressedNode->update();
    pressedNode = nullptr;
    this->InitialNode = nullptr;
}

void GraphViewDfa::setAsInitialNodeRequested(){
    if ( !Node::getIsInitialNodeHasBeenChoosen() ){
        this->InitialNode = pressedNode;
        pressedNode->setThisAsInitialNode();
        pressedNode->update();
    }
    pressedNode = nullptr;
    return;
}

void GraphViewDfa::setAsFinalNodeRequested(){
    pressedNode->setAsFinalNode();
    pressedNode->update();
    pressedNode = nullptr;
    return;
}


void GraphViewDfa::mouseMoveEvent(QMouseEvent *event){
    QPointF scenePt = mapToScene( event->pos() );

    if ( GraphViewDfa::nodeButtonActivated   ) mouseMoveNodeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::edgeButtonActivated   ) mouseMoveEdgeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::selectButtonActivated ) mouseMoveSelectButtonActivated ( scenePt ,event );

    scene-> update();
}

void GraphViewDfa::mouseMoveNodeButtonActivated( QPointF cursorCoordinate ,QMouseEvent* event ){
    scene->removeItem( tempNode );
    if(event->buttons() & Qt::LeftButton){
        tempLine = nullptr;
        tempNode = new Node( cursorCoordinate.x() ,cursorCoordinate.y() );
        scene->addItem( tempNode );
    }
}

void GraphViewDfa::mouseMoveEdgeButtonActivated(QPointF cursorCoordinate, QMouseEvent* event ){
    if ( pressedNode ){
        scene->removeItem( tempLine );
        tempLine = new QGraphicsLineItem( QLineF( pressedNode->getCenterPoint() ,cursorCoordinate ) );
        scene->addItem( tempLine );
    }
}

void GraphViewDfa::mouseMoveSelectButtonActivated(QPointF cursorCoordinate, QMouseEvent* event ){
    if ( pressedNode ){
        pressedNode->setCenterPoint( cursorCoordinate );
        QList <Edge*> edgelist = pressedNode->getEdges();
        for ( Edge* edgeItem : qAsConst(edgelist) ){
            edgeItem->adjust();
        }
        for ( Edge* edgeView : qAsConst( edgeListView ) ){
            edgeView->adjust();
        }
    }
}

void GraphViewDfa::mouseReleaseEvent(QMouseEvent *event){
    QPointF scenePt = mapToScene(event->pos());

    if ( GraphViewDfa::nodeButtonActivated   ) mouseReleaseNodeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::edgeButtonActivated   ) mouseReleaseEdgeButtonActivated   ( scenePt ,event );
    if ( GraphViewDfa::selectButtonActivated ) mouseReleaseSelectButtonActivated ( scenePt ,event );
    if ( GraphViewDfa::removeButtonActivated ) mouseReleaseRemoveButtonActivated ( scenePt ,event );

    scene->update();
}

void GraphViewDfa::mouseReleaseNodeButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    scene->removeItem( tempNode );
    Node *node=new Node( cursorCoordinate.x() ,cursorCoordinate.y() );
    if ( !isInAnyNode( node->getCenterPoint() ) ){
        scene->addItem( node );
        node->setLable( Node::getLableCounter() );
        nodeListView << node;
    }
    tempNode = nullptr;
}

void GraphViewDfa::mouseReleaseEdgeButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    if ( Node* sourceNode = pressedNode ){
        bool removed= false;
        if ( Node * destNode = isInAnyCircle( cursorCoordinate ) ){
           Edge* edge = new Edge( sourceNode ,destNode );
           scene->addItem( edge );
           scene->removeItem( tempLine ); removed =true;
           edge->setEdgeValue( setEdgeValueInputDialog() );
//           edge->setEdgeSubValue( setEdgeValueInputDialog() );
//           edge->setEdgeDirectionValue( setEdgeValueInputDialog() );
           edgeListView << edge;
        }
        //Line which draw onTime
        if (!removed) scene->removeItem( tempLine );
        tempLine = nullptr;
        pressedNode = nullptr;
    }
}

void GraphViewDfa::mouseReleaseSelectButtonActivated(QPointF cursorCoordinate, QMouseEvent * event){
    if ( pressedNode ){
       pressedNode->setCenterPoint( cursorCoordinate );
       QList <Edge*> edgelist = pressedNode->getEdges();
       for ( Edge* edge : qAsConst(edgelist) ){
           edge->adjust();
       }
       pressedNode = nullptr;
    }
}

void GraphViewDfa::mouseReleaseRemoveButtonActivated(QPointF cursorCoordinate, QMouseEvent* event ){
    pressedNode = nullptr;

    if ( Node* node = isInAnyCircle( cursorCoordinate ) ){

        QList<Edge*>::iterator it = edgeListView.begin();
        while (it != edgeListView.end()) {
            if ( (*it)->getDestNode() == node ){
                 //delete edges that thisNode is their destNode
                (*it)->getSourceNode()->deleteEdge( (*it) );
                scene->removeItem( (*it) );
                delete (*it);
                it = edgeListView.erase( it );
            }
            else if ( (*it)->getSourceNode() == node ){
                scene->removeItem( (*it) );
                it = edgeListView.erase( it );
            }
            else ++it;
        }

        QList<Node*>::iterator iterator = nodeListView.begin();
        while (iterator != nodeListView.end()) {
          if ( *iterator == node ){
            iterator = nodeListView.erase(iterator);
            scene->removeItem( node );
            if ( InitialNode == node ){
                node->unSetThisAsInitialNode();
                InitialNode = nullptr;
            }
            node = nullptr;
            break;
          }
          else
            ++iterator;
        }

        scene->update();
    }
}

QString GraphViewDfa::setEdgeValueInputDialog(){
    QString edgeValue = QInputDialog::getText( this ,"" ,"مقدار یال را وارد کنید" );

    return edgeValue == tr("") ? tr("#") : edgeValue;
}

QList<Node*> GraphViewDfa::getNodeListView(){
    return nodeListView;
}

Node* GraphViewDfa::getInitialNode(){
    return InitialNode;
}

void GraphViewDfa::setSceneRender(QPainter * painter){
    scene->render( painter );
}
