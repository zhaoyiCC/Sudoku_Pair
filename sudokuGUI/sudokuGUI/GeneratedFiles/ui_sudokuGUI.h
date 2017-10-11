/********************************************************************************
** Form generated from reading UI file 'sudokuGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKUGUI_H
#define UI_SUDOKUGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sudokuGUIClass
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *sudokuGUIClass)
    {
        if (sudokuGUIClass->objectName().isEmpty())
            sudokuGUIClass->setObjectName(QStringLiteral("sudokuGUIClass"));
        sudokuGUIClass->resize(600, 400);
        action = new QAction(sudokuGUIClass);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(sudokuGUIClass);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(sudokuGUIClass);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(sudokuGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sudokuGUIClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(sudokuGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sudokuGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(sudokuGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        sudokuGUIClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(sudokuGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        sudokuGUIClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(action_3);

        retranslateUi(sudokuGUIClass);

        QMetaObject::connectSlotsByName(sudokuGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *sudokuGUIClass)
    {
        sudokuGUIClass->setWindowTitle(QApplication::translate("sudokuGUIClass", "sudokuGUI", Q_NULLPTR));
        action->setText(QApplication::translate("sudokuGUIClass", "easy", Q_NULLPTR));
        action_2->setText(QApplication::translate("sudokuGUIClass", "normal", Q_NULLPTR));
        action_3->setText(QApplication::translate("sudokuGUIClass", "hard", Q_NULLPTR));
        menu->setTitle(QApplication::translate("sudokuGUIClass", "new game", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sudokuGUIClass: public Ui_sudokuGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKUGUI_H
