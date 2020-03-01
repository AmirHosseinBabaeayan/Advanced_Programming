#include "turing.h"
#include <iostream>

QA::Turing::Turing( Node* initialNode ,std::string input ):DFA( initialNode ,input ),firstFunctionCall(false){
    setHeadTape();
}

QA::Turing::Turing():DFA(){

}

bool QA::Turing::Run(){
    firstFunctionCall = true;
    if ( checkAcceptOrReject( getInitialNode(), getInitialNode(), this->head, this->headTape ) ) {
        appenedStepByStep( getInitialNode() );
        return true;
    }
    return false;
}

char QA::Turing::spilitEdgeValue(std::string string){
    return string.substr( 0, 1)[0];
}

char QA::Turing::spilitSubEdgeValue(std::string string){
    return string.substr( string.find_first_of(";") + 2, 1)[0];
}

char QA::Turing::spilitDirectionEdgeValue(std::string string){
    return string.substr( string.find_first_of(":") + 2, 1)[0];
}

void QA::Turing::setHeadTape(){
    int i = 1;
    char input = parse( 0 );
    while (  input != '&' ) {
        headTape.push_back( input );
        input = parse ( i++ );
    }
    head = headTape.begin();
    headTape.push_back( '#' );
    headTape.push_front( '#' );
}

bool QA::Turing::checkAcceptOrReject(Node* prevNode, Node* currentNode, std::list<char>::iterator _head, std::list<char> headTape ){
    if ( !firstFunctionCall )
    if ( prevNode == currentNode ){
        if ( currentNode->getIsFinalNode() ) {
            headValueStepByStep.push_back( _head );
            headTapeStepByStep.push_back( this->headTape );
            return  true;
        }
        return false;
    }
    firstFunctionCall = false;
    bool isAccepted = false;
    headTape = this->headTape;
    _head = head;
    QList <Edge*> currentNodeEdgeList = currentNode->getEdges();
    for ( Edge* edgeItem : currentNodeEdgeList ){
        if ( *head == spilitEdgeValue( edgeItem->getEdgeValue() ) ){
            *head = spilitSubEdgeValue( edgeItem->getEdgeValue() );
            if ( spilitDirectionEdgeValue( edgeItem->getEdgeValue() ) == 'R' ) increaseHead();
            else decreaseHead();
            if ( edgeItem->getDestNode() != edgeItem->getSourceNode() ) isAccepted = checkAcceptOrReject( currentNode ,edgeItem->getDestNode() ,_head ,headTape );
            else isAccepted = checkAcceptOrReject( prevNode ,currentNode ,_head ,headTape );
            if ( isAccepted ){
                if ( edgeItem->getDestNode() != edgeItem->getSourceNode() ) {
                    appenedStepByStep( edgeItem->getDestNode() );
                    headTapeStepByStep.push_back( headTape );
                    headValueStepByStep.push_back( _head );
                }
                break;
            }
        }
    }
    if ( !isAccepted ) return checkAcceptOrReject( currentNode ,currentNode ,_head ,headTape );
    else return isAccepted;
}

void QA::Turing::increaseHead(){
    head++;
    if ( *head == '#' ) headTape.push_back( '#' );
}

void QA::Turing::decreaseHead(){
    head--;
    if ( *head == '#' ) headTape.push_front( '#' );
}

std::list<char> QA::Turing::getHeadTape(){
    return headTape;
}

std::list< std::list<char>::iterator > QA::Turing::getHeadStepByStep(){
    return headValueStepByStep;
}

std::list< std::list <char> > QA::Turing::getHeadTapeStepByStep(){
    return headTapeStepByStep;
}
