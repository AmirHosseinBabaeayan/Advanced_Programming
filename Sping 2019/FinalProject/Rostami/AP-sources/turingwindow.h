#ifndef TURINGWINDOW_H
#define TURINGWINDOW_H

#include <QMainWindow>
#include "ui_turingwindow.h"
#include "turing.h"

namespace Ui {
class TuringWindow;
}

class TuringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TuringWindow(QMainWindow *parent = nullptr);
    ~TuringWindow();
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
    void on_horizontalSlider_actionTriggered(int action);
    void on_runButton_clicked();
    void on_nextButton_clicked();
    void on_deleteButton_clicked();
    void on_actionRun_Turing_triggered();
    void on_backToMainWindow_clicked();
    void on_actionMultiple_Run_triggered();
    void on_actionMake_PDF_triggered();

    void on_actionSave_triggered();

private:
    QMainWindow* parent;
    Ui::TuringWindow *ui;
    QA::Turing* turing;
};
#endif // TURINGWINDOW_H
