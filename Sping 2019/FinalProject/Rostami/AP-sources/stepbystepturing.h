#ifndef STEPBYSTEPTURING_H
#define STEPBYSTEPTURING_H

#include "stepbystepdfa.h"

class StepByStepTuring : public StepByStepDfa
{
public:
    StepByStepTuring(QWidget* parent = 0);
    void setHeadStepByStep( std::list< std::list<char>::iterator > );
    void setHeadTapeStepByStep( std::list< std::list <char> > );
    void emptyScene() override;

public slots:

protected:
    void drawEdgeValue( int ,Node* ) override;
private:
    std::vector< std::list<char>::iterator > headStepByStep;
    std::vector< std::list <char> > headTapeStepByStep;
    int headTapeStepCounter;
};

#endif // STEPBYSTEPTURING_H
