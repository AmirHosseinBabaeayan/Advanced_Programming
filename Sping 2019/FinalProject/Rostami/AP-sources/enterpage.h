#ifndef ENTERPAGE_H
#define ENTERPAGE_H

#include <QMainWindow>
#include "dfawindow.h"
#include "turingwindow.h"

namespace Ui {
class EnterPage;
}

class EnterPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit EnterPage(QWidget *parent = nullptr);
    ~EnterPage();

private slots:
    void on_DFAButton_clicked();

    void on_TuringButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::EnterPage *ui;
    DfaWindow* dfaWindow;
    TuringWindow* turingWindow;
};

#endif // ENTERPAGE_H
