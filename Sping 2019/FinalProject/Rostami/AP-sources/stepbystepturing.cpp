#include "stepbystepturing.h"
#include <QMessageBox>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <iostream>

StepByStepTuring::StepByStepTuring(QWidget* parent):StepByStepDfa (parent),headTapeStepCounter(0)
{

}

void StepByStepTuring::drawEdgeValue(int index, Node * node){
    std::string lableString = " ";
    std::list<char> headTapeItem = headTapeStepByStep.at( index );
    for ( char value : headTapeItem ){
        lableString += std::string( 1 ,value ) + " ";
    }
    for ( int i = 0 ; i < 20 ; i++ ){
        lableString += "# ";
    }
    QLabel* lable = new QLabel();
    lable->setText( QString::fromStdString( lableString ) );
    QGraphicsProxyWidget* lableWidget = getScene()->addWidget( lable );
    lableWidget->setY( 80 + 100 * headTapeStepCounter++ );
    lableWidget->setX( 0 );
    lableWidget->setZValue( -1 );
}

void StepByStepTuring::setHeadStepByStep(std::list< std::list<char>::iterator > headStepByStep){
    std::vector< std::list<char>::iterator > headStepByStepVector;
    std::list< std::list<char>::iterator >::iterator it = headStepByStep.begin();
    while ( it != headStepByStep.end() ) {
        headStepByStepVector.push_back( *it );
        ++it;
    }
    this->headStepByStep = headStepByStepVector;
}

void StepByStepTuring::setHeadTapeStepByStep(std::list<std::list<char> > headTapeStepByStep){
    std::vector< std::list<char> > headTapeStepByStepVector;
    std::list< std::list<char> >::iterator it = headTapeStepByStep.begin();
    while ( it != headTapeStepByStep.end() ) {
        headTapeStepByStepVector.push_back( *it );
        ++it;
    }
    this->headTapeStepByStep = headTapeStepByStepVector;
}

void StepByStepTuring::emptyScene(){
    StepByStepDfa::emptyScene();
    headTapeStepCounter = 0;
}
