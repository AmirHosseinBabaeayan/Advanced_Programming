#include "edge.h"
#include "node.h"
#define M_PI 3.14
#include <qmath.h>
#include <iostream>
#include <QString>
#include <QLineEdit>

qreal Edge::digitWeigth = 5;

Edge::Edge( Node* sourceNode ,Node* destNode  ):QGraphicsItem ( nullptr ),arrowSize(10),isDuplicated( false ),sameEdgeFlag( false),checkForSameEdgeCounter(0),sameEllipseCounter(2),sameLineCounter(1){
    this->sourceNode = sourceNode;
    this->destNode = destNode;
    adjust();
    sourceNode->addEdge( this );
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Edge::setEdgeValue(QString string ){
    this->value = string.toStdString();
    update();
}

std::string Edge::getEdgeValue( void ){
    return value;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    checkForSymmetryEdge();

    if ( checkForSameEdgeCounter++ < 1 ) checkForSameEdge();

    if ( sameEdgeFlag ) {
        if ( sourceNode == destNode ) drawLable( painter, SameEllipse );
        else drawLable( painter ,SameLine );
        return;
    }

    if ( sourceNode != destNode ){
        if ( getIsDuplicatedFlag() ) drawDupLine( painter );
        else drawSolidLine( painter );
    }

    if ( sourceNode == destNode ) drawReflectiveEdge( painter );

}

void Edge::checkForSameEdge(){
    QList<Edge*> sourceEdges = sourceNode->getEdges();
    for ( Edge* edgeItem : qAsConst(sourceEdges) ){
//check same passed values
        if ( edgeItem->destNode == this->destNode && edgeItem != this ){
                if ( sourceNode == destNode ){
                    this->sameEdgeFlag = true;
                    sameEllipseCounter++;
                }
                else {
                    this->sameEdgeFlag = true;
                    sameLineCounter++;
                }
        }
    }
}

void Edge::checkForSymmetryEdge(){
    QList<Edge*> sourceEdges = sourceNode->getEdges();
    for ( Edge* edgeItem : qAsConst(sourceEdges) ){
//check Duplicate (YAL DOTARAFE) flags
        QList<Edge*> destEdges = edgeItem->getDestNode()->getEdges();
        for ( Edge* destEdgeItem : qAsConst(destEdges) ){
            if ( destEdgeItem->destNode == edgeItem->sourceNode ) {
                destEdgeItem->setIsDuplicatedTrue();
                edgeItem->setIsDuplicatedTrue();
            }
        }
    }
}

void Edge::drawReflectiveEdge( QPainter * painter ){
    QPointF center( sourcePoint.x() ,sourcePoint.y() - RADIUS/2 );
    painter->drawEllipse( center ,RADIUS/2 ,RADIUS/2 );

    painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //arrows
    QPointF collisionAdjust( RADIUS/2 * cos( M_PI - M_PI / 6 ) ,RADIUS/2 * sin( M_PI - M_PI / 6 ) );
    QPointF collisionPoint( center + collisionAdjust );

    QPointF destArrowP1 = center + QPointF( ( RADIUS/2 - 5 ) * cos( M_PI - M_PI / 35 ) ,( RADIUS/2 - 5 ) * sin( M_PI - M_PI / 35 ) );
    QPointF destArrowP2 = center + QPointF( ( RADIUS/2 + 5 ) * cos( M_PI - M_PI / 12 ) ,( RADIUS/2 + 5 ) * sin( M_PI - M_PI / 12 ) );

    painter->drawLine(destArrowP2 , collisionPoint );
    painter->drawLine(destArrowP1 , collisionPoint );

    painter->setPen( QPen() );

    drawLable( painter ,Ellipse );
}


void Edge::drawSolidLine( QPainter* painter ){
    QLineF line(sourcePoint, destPoint);
    painter->drawLine( sourcePoint ,destPoint );

    painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->drawLine(destArrowP1 , destPoint );
    painter->drawLine(destArrowP2 , destPoint );

    painter->setPen( QPen() );

    drawLable( painter ,Line );
}


void Edge::drawDupLine(QPainter * painter ){
    painter->drawPath( shape() );
    painter->drawText( findFractionLinePoint(2*RADIUS/3) + QPointF(-digitWeigth ,0 ) ,QString::fromStdString( value ) );

    painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // Draw the arrows
    QPointF fractionCenterPoint = findFractionLinePoint(RADIUS/4);
    QLineF line( sourcePoint, fractionCenterPoint);
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF destArrowP1 = fractionCenterPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = fractionCenterPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->drawLine(destArrowP1 , fractionCenterPoint );
    painter->drawLine(destArrowP2 , fractionCenterPoint );
//update paint othe edges immediatly
    QList<Edge*> destEdges = this->destNode->getEdges();
    for ( Edge* edgeItem : qAsConst(destEdges) ){
        edgeItem->update();
    }

    return;
}

void Edge::setIsDuplicatedTrue(){
    isDuplicated = true;
}

bool Edge::getIsDuplicatedFlag(){
    return isDuplicated;
}

QPointF Edge::findFractionLinePoint( double fraction ) const{

    QLineF line1( sourceNode->getCenterPoint() ,destNode->getCenterPoint() );
    QLineF normalLine1 = line1.normalVector();
    normalLine1.setLength( fraction );

    QLineF line2( destNode->getCenterPoint() ,sourceNode->getCenterPoint() );
    QLineF normalLine2 = line2.normalVector();
    normalLine2.setLength( fraction );
    normalLine2.setAngle( normalLine2.angle() + 180 );

    QLineF centerLine( normalLine1.p2() ,normalLine2.p2() );

    return centerLine.center();

}

void Edge::drawLable(QPainter * painter ,int type ){
    QLineF line( sourcePoint ,destPoint );
    switch ( type ) {
        case Line :{
                QLineF line( sourcePoint ,destPoint );
                painter->drawText( findFractionLinePoint( RADIUS/2 ) + QPointF(-digitWeigth ,0 ) ,QString::fromStdString( value ) );
            break;
        }
        case Ellipse :{
                painter->drawText( sourceNode->getCenterPoint() + QPointF( -digitWeigth ,-RADIUS - 5 ) ,QString::fromStdString( value ) );
            break;
        }
        case SameLine :{
                painter->drawText( findFractionLinePoint(sameLineCounter* RADIUS/2) + QPointF(-digitWeigth ,0 )  ,QString::fromStdString( value ) );
            break;
        }
        case SameEllipse :{
            painter->drawText( sourceNode->getCenterPoint() + QPointF( -digitWeigth ,-RADIUS/2 * sameEllipseCounter - 5 ),QString::fromStdString( value ) );
            break;
        }
        default:
        break;
    }
}

QRectF Edge::boundingRect() const
{
    if ( sourceNode == destNode ){
        return QRectF( sourcePoint.x() - RADIUS/2 ,sourcePoint.y() - RADIUS ,RADIUS ,RADIUS )
               .adjusted( -arrowSize, -arrowSize, arrowSize, arrowSize).adjusted( 0, -RADIUS/2 * sameEllipseCounter, 0, 0);
    }

    QLineF line( sourcePoint ,destPoint );
    int adjustValue = RADIUS/2 * sameLineCounter + digitWeigth;
    //normal bounding rect
     return QRectF(sourcePoint , QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted( -arrowSize, -arrowSize, arrowSize, arrowSize).adjusted( -adjustValue ,-adjustValue ,adjustValue ,adjustValue );

}


QPainterPath Edge::shape() const{
    QPainterPath path;
    path.moveTo( sourcePoint );
    QLineF line( sourcePoint ,destPoint );
    path.cubicTo( line.center() ,findFractionLinePoint(2*RADIUS/3) , destPoint );
    return path;
}

void Edge::adjust()
{
    //adjust to sourcePoint and destPoint
    if ( sourceNode == destNode ){
        sourcePoint = destPoint = sourceNode->getCenterPoint();
        return;
    }

    QLineF line( sourceNode->getCenterPoint() ,destNode->getCenterPoint() );


    qreal length = line.length();
    prepareGeometryChange();

        QPointF edgeOffset((line.dx() * RADIUS/2) / length, (line.dy() * RADIUS/2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint   = line.p2() - edgeOffset;
        update();
}


Node* Edge::getSourceNode() const
{
    return sourceNode;
}

Node* Edge::getDestNode() const
{
    return destNode;
}

void Edge::setDigitWeigth(qreal weigth){
    digitWeigth = weigth;
}
