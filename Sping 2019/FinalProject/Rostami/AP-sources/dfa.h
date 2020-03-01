#ifndef DFA_H
#define DFA_H

#include "edge.h"
#include "node.h"

namespace QA {
    class DFA
    {
    public:
        DFA( Node* ,std::string );
        DFA();
        virtual ~DFA();
        virtual bool Run();
        void setCurrentNode( Node* );
        Node* getCurrentNode( void );
        Node* setInitialNode( Node* );
        Node* getInitialNode( void );
        QList<Node*> getStepByStepNode( void );
        QList<Edge*> getStepByStepEdge( void );

    protected:
        bool checkAcceptOrReject( Node* ,char ,int );
        char  parse(int i);
        bool  setInput( std::string );
        void appenedStepByStep( Node* );
        void appenedStepByStep( Edge* );

    private:
        std::string input;
        Node* currentNode;
        Node* initialNode;
        QList<Node*> stepByStepNode;
        QList<Edge*> stepByStepEdge;
    };
}

#endif // DFA_H
