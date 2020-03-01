/********************************************************************************
** Form generated from reading UI file 'dfawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DFAWINDOW_H
#define UI_DFAWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "graphviewdfa.h"
#include "stepbystepdfa.h"

QT_BEGIN_NAMESPACE

class Ui_DfaWindow
{
public:
    QAction *actionRun_DFA;
    QAction *actionSave_As;
    QAction *actionSave;
    QAction *actionMake_PDF;
    QAction *actionMultiple_input;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_3;
    GraphViewDfa *graphicsView;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSlider;
    StepByStepDfa *stepByStepView;
    QPushButton *runButton;
    QPushButton *nextButton;
    QPushButton *deleteButton;
    QPushButton *backToMainWindow;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DfaWindow)
    {
        if (DfaWindow->objectName().isEmpty())
            DfaWindow->setObjectName(QString::fromUtf8("DfaWindow"));
        DfaWindow->resize(803, 528);
        DfaWindow->setAcceptDrops(false);
        DfaWindow->setStyleSheet(QString::fromUtf8(""));
        DfaWindow->setDocumentMode(false);
        actionRun_DFA = new QAction(DfaWindow);
        actionRun_DFA->setObjectName(QString::fromUtf8("actionRun_DFA"));
        actionSave_As = new QAction(DfaWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionSave = new QAction(DfaWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionMake_PDF = new QAction(DfaWindow);
        actionMake_PDF->setObjectName(QString::fromUtf8("actionMake_PDF"));
        actionMultiple_input = new QAction(DfaWindow);
        actionMultiple_input->setObjectName(QString::fromUtf8("actionMultiple_input"));
        centralWidget = new QWidget(DfaWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 32, 32));
        pushButton->setStyleSheet(QString::fromUtf8("border-radius :  10px ;\n"
"background:  #9EA8AD;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/img/iconfinder_add_134224.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(20, 20));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 10, 32, 32));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/img/left-and-right-arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(20, 20));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(130, 10, 32, 32));
        pushButton_6->setTabletTracking(false);
        pushButton_6->setFocusPolicy(Qt::ClickFocus);
        pushButton_6->setContextMenuPolicy(Qt::NoContextMenu);
        pushButton_6->setStyleSheet(QString::fromUtf8("\n"
"\n"
"border-radius : 10px; \n"
"background: #9EA8AD;\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/img/noun_Delete_5493.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon2);
        pushButton_6->setIconSize(QSize(20, 20));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(90, 10, 32, 32));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/img/32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon3);
        graphicsView = new GraphViewDfa(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 50, 601, 401));
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(3000, 2000));
        graphicsView->setSizeIncrement(QSize(0, 0));
        graphicsView->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 10, 441, 32));
        label->setStyleSheet(QString::fromUtf8("background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0.0149254 rgba(56, 134, 224, 215), stop:1 rgba(239, 239, 239, 239));\n"
"border-radius: 10px;\n"
""));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(620, 10, 171, 32));
        label_2->setStyleSheet(QString::fromUtf8("background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0.0149254 rgba(239, 239, 239, 239), stop:1 rgba(56, 134, 224, 215));\n"
"border-radius: 10px;\n"
""));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 460, 781, 21));
        horizontalSlider->setOrientation(Qt::Horizontal);
        stepByStepView = new StepByStepDfa(centralWidget);
        stepByStepView->setObjectName(QString::fromUtf8("stepByStepView"));
        stepByStepView->setGeometry(QRect(620, 50, 171, 361));
        stepByStepView->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: #C3E4F6  ;\n"
"border: 0.5px solid #0E7BDC;"));
        runButton = new QPushButton(centralWidget);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setGeometry(QRect(730, 420, 30, 30));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        runButton->setFont(font);
        runButton->setAutoFillBackground(false);
        runButton->setStyleSheet(QString::fromUtf8("\n"
"border-radius : 10px; \n"
"background: #9EA8AD;\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/img/2873-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        runButton->setIcon(icon4);
        runButton->setIconSize(QSize(20, 20));
        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(690, 420, 30, 30));
        nextButton->setFont(font);
        nextButton->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/img/207-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon5);
        nextButton->setIconSize(QSize(20, 20));
        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(650, 420, 30, 30));
        deleteButton->setFont(font);
        deleteButton->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/img/broom_clean_clear_sweep_housework_dust-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon6);
        deleteButton->setIconSize(QSize(20, 20));
        backToMainWindow = new QPushButton(centralWidget);
        backToMainWindow->setObjectName(QString::fromUtf8("backToMainWindow"));
        backToMainWindow->setGeometry(QRect(760, 10, 31, 31));
        backToMainWindow->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/img/890784-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        backToMainWindow->setIcon(icon7);
        backToMainWindow->setIconSize(QSize(50, 50));
        DfaWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DfaWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 803, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        DfaWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(DfaWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(212, 113, 245, 255), stop:1 rgba(239, 239, 239, 239))\n"
""));
        DfaWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionRun_DFA);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionMake_PDF);
        menuFile->addAction(actionMultiple_input);

        retranslateUi(DfaWindow);

        pushButton_6->setDefault(false);


        QMetaObject::connectSlotsByName(DfaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DfaWindow)
    {
        DfaWindow->setWindowTitle(QCoreApplication::translate("DfaWindow", "\331\276\330\261\331\210\332\230\331\207 \331\276\330\247\333\214\330\247\331\206\333\214 \330\250\330\261\331\206\330\247\331\205\331\207 \330\263\330\247\330\262\333\214 \331\276\333\214\330\264\330\261\331\201\330\252\331\207", nullptr));
        actionRun_DFA->setText(QCoreApplication::translate("DfaWindow", "Run DFA", nullptr));
        actionSave_As->setText(QCoreApplication::translate("DfaWindow", "Save As...", nullptr));
        actionSave->setText(QCoreApplication::translate("DfaWindow", "Save As PNG", nullptr));
        actionMake_PDF->setText(QCoreApplication::translate("DfaWindow", "Make PDF", nullptr));
        actionMultiple_input->setText(QCoreApplication::translate("DfaWindow", "Multiple input...", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_6->setText(QString());
        pushButton_3->setText(QString());
        label->setText(QCoreApplication::translate("DfaWindow", "   \331\205\330\247\330\264\333\214\331\206 \330\257\333\214 \330\247\331\201 \330\247\333\214 ", nullptr));
        label_2->setText(QCoreApplication::translate("DfaWindow", "                \331\206\331\205\330\247\333\214\330\264 \332\257\330\247\331\205 \330\250\331\207 \332\257\330\247\331\205", nullptr));
        runButton->setText(QString());
        nextButton->setText(QString());
        deleteButton->setText(QString());
        backToMainWindow->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("DfaWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DfaWindow: public Ui_DfaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DFAWINDOW_H
