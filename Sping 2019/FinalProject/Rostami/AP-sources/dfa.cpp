#include "dfa.h"

QA::DFA::DFA( Node* initialNode ,std::string input ){
    setCurrentNode( initialNode );
    setInitialNode( initialNode );
    setInput( input );
}

QA::DFA::DFA(){

}

QA::DFA::~DFA(){
}

bool QA::DFA::Run(){
    int i = 0;
    if ( checkAcceptOrReject( currentNode, parse(i), i ) ) {
        stepByStepNode << initialNode;
        return true;
    }
    else return false;
}

bool QA::DFA::checkAcceptOrReject(Node * currentNode, char currentInput, int i ){
    if ( currentInput == '&' ){
        if ( currentNode->getIsFinalNode() == true ) return true;
        else return false;
    }
    bool isAccepted = false;
    QList <Edge*> currentNodeEdgesList = currentNode->getEdges();
    for ( Edge* edgeItem : currentNodeEdgesList ){
        if ( *edgeItem->getEdgeValue().c_str() == currentInput ){
            isAccepted = checkAcceptOrReject( edgeItem->getDestNode(), parse(i + 1), i + 1 );
        }
        if ( isAccepted ) {
            appenedStepByStep( edgeItem->getDestNode() );
            appenedStepByStep( edgeItem );
            break;
        }
    }
    return isAccepted;
}

void QA::DFA::setCurrentNode( Node* node){
    if ( node != nullptr ) {
        currentNode = node;
    }
}

char QA::DFA::parse(int i){
    if ( i != input.length() ) return input[ i ];
    else return '&';
}

Node* QA::DFA::getCurrentNode( void ){
    return currentNode;
}

QList<Node*> QA::DFA::getStepByStepNode(){
    return stepByStepNode;
}

QList<Edge*> QA::DFA::getStepByStepEdge(){
    return stepByStepEdge;
}

void QA::DFA::appenedStepByStep(Node * node){
    stepByStepNode.push_back( node );
}

void QA::DFA::appenedStepByStep(Edge * edge){
    stepByStepEdge.push_back( edge );
}

bool QA::DFA::setInput(std::string input){
    if ( input != "" ){
        this->input = input;
        return true;
    }
    else return false;
}

Node* QA::DFA::setInitialNode( Node * node ){
    if ( node != nullptr ) {
        this->initialNode = node;
        return node;
    }
    else return nullptr;
}

Node* QA::DFA::getInitialNode(){
    return initialNode;
}
