#ifndef GRAPHVIEWTURING_H
#define GRAPHVIEWTURING_H

#include "graphviewdfa.h"

class GraphViewTuring : public GraphViewDfa
{
    Q_OBJECT
public:
    GraphViewTuring(QWidget* parent = 0);
    QString setEdgeValueInputDialog() override;
public slots:

protected:

private:

};

#endif // GRAPHVIEWTURING_H
