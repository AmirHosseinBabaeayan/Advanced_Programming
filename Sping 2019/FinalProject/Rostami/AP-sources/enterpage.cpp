#include "enterpage.h"
#include "ui_enterpage.h"

EnterPage::EnterPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EnterPage)
{
    ui->setupUi(this);
    setMaximumSize( this->size() );
    setMinimumSize( this->size() );
    this->move( 550 , 150 );
}

EnterPage::~EnterPage()
{
    delete ui;
}

void EnterPage::on_DFAButton_clicked()
{
    dfaWindow = new DfaWindow(this);
    this->close();
    dfaWindow->show();
}

void EnterPage::on_TuringButton_clicked()
{
    turingWindow = new TuringWindow(this);
    this->close();
    turingWindow->show();
}

void EnterPage::on_ExitButton_clicked()
{
    this->close();
}
