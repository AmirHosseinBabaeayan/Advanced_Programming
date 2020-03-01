/********************************************************************************
** Form generated from reading UI file 'turingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURINGWINDOW_H
#define UI_TURINGWINDOW_H

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
#include <graphviewturing.h>
#include <stepbystepturing.h>

QT_BEGIN_NAMESPACE

class Ui_TuringWindow
{
public:
    QAction *actionRun_Turing;
    QAction *actionSave_AS;
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionMake_PDF;
    QAction *actionMultiple_Run;
    QWidget *centralwidget;
    QPushButton *runButton;
    QSlider *horizontalSlider;
    QPushButton *pushButton_3;
    StepByStepTuring *stepByStepView;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *nextButton;
    QLabel *label_2;
    QPushButton *pushButton_6;
    GraphViewTuring *graphicsView;
    QPushButton *deleteButton;
    QPushButton *pushButton;
    QPushButton *backToMainWindow;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TuringWindow)
    {
        if (TuringWindow->objectName().isEmpty())
            TuringWindow->setObjectName(QString::fromUtf8("TuringWindow"));
        TuringWindow->resize(803, 528);
        actionRun_Turing = new QAction(TuringWindow);
        actionRun_Turing->setObjectName(QString::fromUtf8("actionRun_Turing"));
        actionSave_AS = new QAction(TuringWindow);
        actionSave_AS->setObjectName(QString::fromUtf8("actionSave_AS"));
        actionSave = new QAction(TuringWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionOpen = new QAction(TuringWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionMake_PDF = new QAction(TuringWindow);
        actionMake_PDF->setObjectName(QString::fromUtf8("actionMake_PDF"));
        actionMultiple_Run = new QAction(TuringWindow);
        actionMultiple_Run->setObjectName(QString::fromUtf8("actionMultiple_Run"));
        centralwidget = new QWidget(TuringWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        runButton = new QPushButton(centralwidget);
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/img/2873-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        runButton->setIcon(icon);
        runButton->setIconSize(QSize(20, 20));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 460, 781, 21));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(90, 10, 32, 32));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/img/32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon1);
        stepByStepView = new StepByStepTuring(centralwidget);
        stepByStepView->setObjectName(QString::fromUtf8("stepByStepView"));
        stepByStepView->setGeometry(QRect(620, 50, 171, 361));
        stepByStepView->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: #AFF8B1  ;\n"
"border: 0.5px solid #0B6C0E;"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 10, 32, 32));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/img/left-and-right-arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon2);
        pushButton_2->setIconSize(QSize(20, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 10, 441, 32));
        label->setStyleSheet(QString::fromUtf8("background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0.0149254 rgba(65, 245, 71, 215), stop:1 rgba(239, 239, 239, 239));\n"
"border-radius: 10px;\n"
""));
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(690, 420, 30, 30));
        nextButton->setFont(font);
        nextButton->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/img/207-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon3);
        nextButton->setIconSize(QSize(20, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(620, 10, 171, 32));
        label_2->setStyleSheet(QString::fromUtf8("background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0.0149254 rgba(239, 239, 239, 239), stop:1 rgba(65, 245, 71, 215));\n"
"border-radius: 10px;\n"
"\n"
""));
        pushButton_6 = new QPushButton(centralwidget);
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/img/noun_Delete_5493.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon4);
        pushButton_6->setIconSize(QSize(20, 20));
        graphicsView = new GraphViewTuring(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 50, 601, 401));
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(3000, 2000));
        graphicsView->setSizeIncrement(QSize(0, 0));
        graphicsView->setStyleSheet(QString::fromUtf8(""));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(650, 420, 30, 30));
        deleteButton->setFont(font);
        deleteButton->setStyleSheet(QString::fromUtf8("border-radius : 10px; \n"
"background: #9EA8AD;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/img/broom_clean_clear_sweep_housework_dust-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon5);
        deleteButton->setIconSize(QSize(20, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 32, 32));
        pushButton->setStyleSheet(QString::fromUtf8("border-radius :  10px ;\n"
"background:  #9EA8AD;"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/img/iconfinder_add_134224.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon6);
        pushButton->setIconSize(QSize(20, 20));
        backToMainWindow = new QPushButton(centralwidget);
        backToMainWindow->setObjectName(QString::fromUtf8("backToMainWindow"));
        backToMainWindow->setGeometry(QRect(760, 10, 31, 31));
        backToMainWindow->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/img/890784-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        backToMainWindow->setIcon(icon7);
        backToMainWindow->setIconSize(QSize(50, 50));
        TuringWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TuringWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 803, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        TuringWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TuringWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(96, 252, 100, 255), stop:1 rgba(239, 239, 239, 239))\n"
""));
        TuringWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionRun_Turing);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionMake_PDF);
        menuFile->addAction(actionMultiple_Run);

        retranslateUi(TuringWindow);

        pushButton_6->setDefault(false);


        QMetaObject::connectSlotsByName(TuringWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TuringWindow)
    {
        TuringWindow->setWindowTitle(QCoreApplication::translate("TuringWindow", "MainWindow", nullptr));
        actionRun_Turing->setText(QCoreApplication::translate("TuringWindow", "Run Turing", nullptr));
        actionSave_AS->setText(QCoreApplication::translate("TuringWindow", "Save AS...", nullptr));
        actionSave->setText(QCoreApplication::translate("TuringWindow", " Save As PNG", nullptr));
        actionOpen->setText(QCoreApplication::translate("TuringWindow", "Open", nullptr));
        actionMake_PDF->setText(QCoreApplication::translate("TuringWindow", "Make PDF", nullptr));
        actionMultiple_Run->setText(QCoreApplication::translate("TuringWindow", "Multiple Run...", nullptr));
        runButton->setText(QString());
        pushButton_3->setText(QString());
        pushButton_2->setText(QString());
        label->setText(QCoreApplication::translate("TuringWindow", "   \331\205\330\247\330\264\333\214\331\206 \330\252\331\210\330\261\333\214\331\206\332\257", nullptr));
        nextButton->setText(QString());
        label_2->setText(QCoreApplication::translate("TuringWindow", "                \331\206\331\205\330\247\333\214\330\264 \332\257\330\247\331\205 \330\250\331\207 \332\257\330\247\331\205", nullptr));
        pushButton_6->setText(QString());
        deleteButton->setText(QString());
        pushButton->setText(QString());
        backToMainWindow->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("TuringWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TuringWindow: public Ui_TuringWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURINGWINDOW_H
