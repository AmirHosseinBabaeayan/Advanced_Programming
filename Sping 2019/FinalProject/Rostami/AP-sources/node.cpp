#include "node.h"
#include"edge.h"
#include"graphviewdfa.h"
#include "dfawindow.h"
#include "turingwindow.h"
#include<QPainter>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#define RADIUS 40

QColor Node::color = QColor(64, 195, 248);
bool Node::isInitialNodeHasBeenChoosen = false;
unsigned int Node::counter = 0;

Node::Node( qreal x, qreal y )
    : QGraphicsItem ( nullptr ), isFinalNode( false ), thisIsInitalNode( false ),nodeLable(""),displayNode(false)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    center.setX( x );
    center.setY( y );
}

Node::Node():QGraphicsItem ( nullptr ), isFinalNode( false ), thisIsInitalNode( false ),nodeLable(""){

}

unsigned int Node::getLableCounter(){
    return counter++;
}

void Node::setAsFinalNode(){
    isFinalNode = !isFinalNode;
    return;
}

bool Node::getIsFinalNode(){
    return isFinalNode;
}

QRectF Node::boundingRect() const {
    qreal adjust = 5;
    return QRectF( center.x() -RADIUS/2 - adjust ,center.y() - RADIUS/2 - adjust ,RADIUS + 2*adjust ,RADIUS + 2*adjust )
            .adjusted( -RADIUS/2 ,0 ,0 ,0 );
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse( center ,RADIUS/2 ,RADIUS/2 );
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(QBrush( Node::color, Qt::SolidPattern));
    painter->drawPath( shape() );
    painter->setBrush(QBrush() );

    if ( this->thisIsInitalNode ) drawInitialNodeStyle( painter );
    if ( this->displayNode ) drawAsDisplayed( painter );


    if ( this->isFinalNode ) drawAsFinal( painter );
    QPointF digitWeigth( -10, 5);
    painter->drawText( center + digitWeigth ,nodeLable );
}

void Node::setLable(unsigned int counter){
    nodeLable = QString::fromStdString( "N" + std::to_string( counter ) );
}

void Node::setLable(std::string lable){
    this->nodeLable = QString::fromStdString( lable );
}

void Node::setdisplayed(){
    displayNode = true;
}

void Node::setHidden(){
    displayNode = false;
}

void Node::drawAsDisplayed(QPainter * painter){
    painter->setBrush( Qt::gray );
    painter->drawEllipse( this->center ,RADIUS/2 ,RADIUS/2 );
}

void Node::drawInitialNodeStyle(QPainter * painter){
    painter->setPen( QPen() );
    QColor color(190, 212, 152);
    painter->setBrush(color);

    QPointF first ( this->get_X() - RADIUS/2, this->get_Y() );
    QPointF second( this->get_X() - RADIUS  , this->get_Y() - RADIUS/2 );
    QPointF third ( this->get_X() - RADIUS  , this->get_Y() + RADIUS/2 );

    painter->drawPolygon( QPolygonF() << first << second << third );
}

void Node::drawAsFinal(QPainter * painter){
    painter->setPen( QPen() );
    QColor color(25, 234, 133);
    painter->setBrush( color );
    painter->drawEllipse( this->center ,RADIUS/2.5 ,RADIUS/2.5 );
    painter->setOpacity( 1 );
    return;
}

void Node::setThisAsInitialNode(){
    Node::isInitialNodeHasBeenChoosen = true;
    this->thisIsInitalNode = true;
}

void Node::unSetThisAsInitialNode(){
    Node::isInitialNodeHasBeenChoosen = false;
    this->thisIsInitalNode = false;
}

bool Node::getIsInitialNodeHasBeenChoosen(){
    return Node::isInitialNodeHasBeenChoosen;
}

Edge* Node::addEdge(Edge *edge)
{
     edgeList << edge;
     edge->adjust();
}

void Node::deleteEdge(Edge* edgeItem){
    QList<Edge*>::iterator it = edgeList.begin();
    while( it != edgeList.end() ){
        if ( (*it) == edgeItem ){
            it = edgeList.erase( it );
        }
        else ++it;
    }
}
QList < Edge* > Node::getEdges(){
    return edgeList;
}

void Node::set_X(qreal x){
    center.setX( x );
}

void Node::set_Y(qreal y){
    center.setY( y );
}

qreal Node::get_X(void){
    return center.x();
}
qreal Node::get_Y(void){
    return center.y();
}

void Node::setCenterPoint(QPointF point ){
    this->center = point;
}

QPointF Node::getCenterPoint(){
    return this->center;
}

std::string Node::getLable(){
    std::string string = nodeLable.toStdString();
    return string;
}
