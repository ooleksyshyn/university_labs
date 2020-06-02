/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Wakers;
    QPushButton *Timers;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *TimersAndWakers;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Add;
    QPushButton *Delete;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *message;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLabel *description;
    QLineEdit *messageEdit;
    QCheckBox *DoNotDisturb;
    QCheckBox *ShowActive;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(661, 510);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(-1, 0, 661, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Wakers = new QPushButton(horizontalLayoutWidget);
        Wakers->setObjectName(QStringLiteral("Wakers"));

        horizontalLayout->addWidget(Wakers);

        Timers = new QPushButton(horizontalLayoutWidget);
        Timers->setObjectName(QStringLiteral("Timers"));

        horizontalLayout->addWidget(Timers);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 40, 331, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TimersAndWakers = new QListWidget(verticalLayoutWidget);
        TimersAndWakers->setObjectName(QStringLiteral("TimersAndWakers"));

        verticalLayout->addWidget(TimersAndWakers);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(339, 40, 321, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Add = new QPushButton(horizontalLayoutWidget_2);
        Add->setObjectName(QStringLiteral("Add"));

        horizontalLayout_2->addWidget(Add);

        Delete = new QPushButton(horizontalLayoutWidget_2);
        Delete->setObjectName(QStringLiteral("Delete"));

        horizontalLayout_2->addWidget(Delete);

        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(340, 90, 321, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        message = new QLabel(horizontalLayoutWidget_3);
        message->setObjectName(QStringLiteral("message"));

        horizontalLayout_3->addWidget(message);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(340, 160, 321, 32));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(verticalLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        description = new QLabel(centralWidget);
        description->setObjectName(QStringLiteral("description"));
        description->setGeometry(QRect(340, 200, 319, 59));
        messageEdit = new QLineEdit(centralWidget);
        messageEdit->setObjectName(QStringLiteral("messageEdit"));
        messageEdit->setGeometry(QRect(340, 280, 319, 30));
        DoNotDisturb = new QCheckBox(centralWidget);
        DoNotDisturb->setObjectName(QStringLiteral("DoNotDisturb"));
        DoNotDisturb->setGeometry(QRect(340, 330, 151, 28));
        ShowActive = new QCheckBox(centralWidget);
        ShowActive->setObjectName(QStringLiteral("ShowActive"));
        ShowActive->setGeometry(QRect(340, 370, 171, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 661, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Wakers->setText(QApplication::translate("MainWindow", "Waker", Q_NULLPTR));
        Timers->setText(QApplication::translate("MainWindow", "Timer", Q_NULLPTR));
        Add->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        Delete->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        message->setText(QApplication::translate("MainWindow", "Enter new timer (hh:mm:ss):", Q_NULLPTR));
        description->setText(QApplication::translate("MainWindow", "Enter message:", Q_NULLPTR));
        DoNotDisturb->setText(QApplication::translate("MainWindow", "Do not disturb", Q_NULLPTR));
        ShowActive->setText(QApplication::translate("MainWindow", "Show only active", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
