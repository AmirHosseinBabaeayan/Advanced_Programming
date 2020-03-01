/********************************************************************************
** Form generated from reading UI file 'enterpage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERPAGE_H
#define UI_ENTERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnterPage
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *DFAButton;
    QPushButton *TuringButton;
    QPushButton *ActiveButton;
    QPushButton *GuideButton;
    QPushButton *ExitButton;
    QLabel *label_2;

    void setupUi(QMainWindow *EnterPage)
    {
        if (EnterPage->objectName().isEmpty())
            EnterPage->setObjectName(QString::fromUtf8("EnterPage"));
        EnterPage->setWindowModality(Qt::ApplicationModal);
        EnterPage->resize(461, 547);
        EnterPage->setStyleSheet(QString::fromUtf8("QPushButton#DFAButton{\n"
"border-radius: 5px;\n"
"background-repeat:  norepeat;\n"
"	font: 75 15pt \"Titr\";\n"
"}\n"
"\n"
"QPushButton#TuringButton{\n"
"border-radius: 5px;\n"
"background-repeat:  norepeat;\n"
"	font: 75 15pt \"Titr\";\n"
"}\n"
"QPushButton#ActiveButton{\n"
"border-radius: 5px;\n"
"background-repeat:  norepeat;\n"
"	font: 75 15pt \"Titr\";\n"
"}\n"
"QPushButton#GuideButton{\n"
"border-radius: 5px;\n"
"background-repeat:  norepeat;\n"
"	font: 75 15pt \"Titr\";\n"
"}\n"
"QPushButton#ExitButton{\n"
"border-radius: 5px;\n"
"background-repeat:  norepeat;\n"
"	font: 75 15pt \"Titr\";\n"
"}\n"
"\n"
"QPushButton#DFAButton:hover{\n"
"background-image:url(:/img/img/buttons/HoverButton.png);\n"
"}\n"
"QPushButton#DFAButton:pressed{\n"
"background-image:url(:/img/img/buttons/PressedButton.png);\n"
"}\n"
"QPushButton#TuringButton:hover{\n"
"background-image:url(:/img/img/buttons/HoverButton.png);\n"
"}\n"
"QPushButton#TuringButton:pressed{\n"
"background-image:url(:/img/img/buttons/PressedButton.png);\n"
""
                        "}\n"
"QPushButton#ActiveButton:hover{\n"
"background-image:url(:/img/img/buttons/HoverButton.png);\n"
"}\n"
"QPushButton#ActiveButton:pressed{\n"
"background-image:url(:/img/img/buttons/PressedButton.png);\n"
"}\n"
"QPushButton#GuideButton:hover{\n"
"background-image:url(:/img/img/buttons/HoverButton.png);\n"
"}\n"
"QPushButton#GuideButton:pressed{\n"
"background-image:url(:/img/img/buttons/PressedButton.png);\n"
"}\n"
"QPushButton#ExitButton:hover{\n"
"background-image:url(:/img/img/buttons/HoverButton.png);\n"
"}\n"
"QPushButton#ExitButton:pressed{\n"
"background-image:url(:/img/img/buttons/PressedButton.png);\n"
"}\n"
""));
        centralwidget = new QWidget(EnterPage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-7, 0, 468, 550));
        label->setAutoFillBackground(true);
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/img/button.jpg")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label->setWordWrap(false);
        label->setMargin(0);
        label->setIndent(0);
        DFAButton = new QPushButton(centralwidget);
        DFAButton->setObjectName(QString::fromUtf8("DFAButton"));
        DFAButton->setGeometry(QRect(90, 44, 275, 72));
        QFont font;
        font.setFamily(QString::fromUtf8("Titr"));
        font.setPointSize(15);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        DFAButton->setFont(font);
        DFAButton->setStyleSheet(QString::fromUtf8(""));
        TuringButton = new QPushButton(centralwidget);
        TuringButton->setObjectName(QString::fromUtf8("TuringButton"));
        TuringButton->setGeometry(QRect(90, 135, 275, 72));
        TuringButton->setFont(font);
        TuringButton->setStyleSheet(QString::fromUtf8(""));
        ActiveButton = new QPushButton(centralwidget);
        ActiveButton->setObjectName(QString::fromUtf8("ActiveButton"));
        ActiveButton->setGeometry(QRect(90, 225, 275, 72));
        ActiveButton->setFont(font);
        ActiveButton->setStyleSheet(QString::fromUtf8(""));
        GuideButton = new QPushButton(centralwidget);
        GuideButton->setObjectName(QString::fromUtf8("GuideButton"));
        GuideButton->setGeometry(QRect(90, 316, 275, 72));
        GuideButton->setFont(font);
        GuideButton->setStyleSheet(QString::fromUtf8(""));
        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));
        ExitButton->setGeometry(QRect(90, 406, 275, 71));
        ExitButton->setFont(font);
        ExitButton->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(156, 520, 141, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Chancery L"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(9);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(211, 215, 207);\n"
"font: 75 italic 11pt \"URW Chancery L\";"));
        EnterPage->setCentralWidget(centralwidget);
#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(EnterPage);

        QMetaObject::connectSlotsByName(EnterPage);
    } // setupUi

    void retranslateUi(QMainWindow *EnterPage)
    {
        EnterPage->setWindowTitle(QCoreApplication::translate("EnterPage", "\330\250\330\261\331\206\330\247\331\205\331\207 \330\263\330\247\330\262\333\214 \331\276\333\214\330\264\330\261\331\201\330\252\331\207 \333\271\333\267\333\262", nullptr));
        label->setText(QString());
        DFAButton->setText(QCoreApplication::translate("EnterPage", "\330\263\330\247\330\256\330\252 \331\205\330\247\330\264\333\214\331\206 \330\257\333\214 \330\247\331\201 \330\247\333\214", nullptr));
        TuringButton->setText(QCoreApplication::translate("EnterPage", "\330\263\330\247\330\256\330\252 \331\205\330\247\330\264\333\214\331\206 \330\252\331\210\330\261\333\214\331\206\332\257", nullptr));
        ActiveButton->setText(QCoreApplication::translate("EnterPage", "\330\261\330\247\331\207\331\206\331\205\330\247\333\214 \330\250\330\261\331\206\330\247\331\205\331\207", nullptr));
        GuideButton->setText(QCoreApplication::translate("EnterPage", "\331\201\330\271\330\247\331\204\330\263\330\247\330\262\333\214 \330\250\330\261\331\206\330\247\331\205\331\207", nullptr));
        ExitButton->setText(QCoreApplication::translate("EnterPage", "\330\256\330\261\331\210\330\254", nullptr));
        label_2->setText(QCoreApplication::translate("EnterPage", "2019 @ all rigths reseved", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnterPage: public Ui_EnterPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERPAGE_H
