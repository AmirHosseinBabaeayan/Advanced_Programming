#ifndef TURING_H
#define TURING_H

#include "dfa.h"

namespace QA{
    class Turing : public QA::DFA
    {
        public:
            Turing( Node* ,std::string );
            Turing();
            bool Run() override;
            bool checkAcceptOrReject( Node* ,Node* ,std::list<char>::iterator ,std::list<char> );
            char spilitEdgeValue( std::string );
            char spilitSubEdgeValue( std::string );
            char spilitDirectionEdgeValue( std::string );
            std::list<char> getHeadTape();
            std::list< std::list<char>::iterator > getHeadStepByStep();
            std::list< std::list <char> > getHeadTapeStepByStep();
            void setHeadTape();
            void increaseHead();
            void decreaseHead();

        private:
            std::list<char> headTape;
            std::list<char>::iterator head;
            std::list< std::list<char>::iterator > headValueStepByStep;
            std::list< std::list <char> > headTapeStepByStep;
            bool firstFunctionCall;
    };
}
#endif // TURING_H
