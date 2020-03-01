#ifndef DFAWINDOW_H
#define DFAWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include "graphviewdfa.h"
#include "dfa.h"

namespace Ui {
class DfaWindow;
}

class DfaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DfaWindow(QMainWindow *parent = nullptr);
    ~DfaWindow();
    void setStepByStep();
protected:
    void scaleView(qreal scaleFactor);
    void showSuccesfullMessage();
    void showFailedMessage();
    void disableAllButtons();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_actionRun_DFA_triggered();
    void on_horizontalSlider_actionTriggered(int action);
    void on_runButton_clicked();
    void on_nextButton_clicked();
    void on_deleteButton_clicked();
    void on_backToMainWindow_clicked();
    void on_actionMultiple_input_triggered();
    void on_actionMake_PDF_triggered();
    void on_actionSave_triggered();

private:
    QMainWindow* parent;
    Ui::DfaWindow *ui;
    QA::DFA* dfa;
};

#endif DFAWINDOW_H
