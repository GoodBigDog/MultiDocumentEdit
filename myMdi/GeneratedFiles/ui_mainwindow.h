/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClose;
    QAction *actionCloseAll;
    QAction *actionTile;
    QAction *actionCascade;
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_E;
    QMenu *menu_W;
    QMenu *menu_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1046, 628);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/ico/Documents Folder.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\346\226\260\345\273\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\346\211\223\345\274\200.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\344\277\235\345\255\230.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionSaveAs = new QAction(MainWindowClass);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\345\217\246\345\255\230\344\270\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon4);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionUndo = new QAction(MainWindowClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\346\222\244\351\224\200.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindowClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\346\201\242\345\244\215.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon6);
        actionCut = new QAction(MainWindowClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(MainWindowClass);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindowClass);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionCloseAll = new QAction(MainWindowClass);
        actionCloseAll->setObjectName(QStringLiteral("actionCloseAll"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\345\205\263\351\227\255.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloseAll->setIcon(icon7);
        actionTile = new QAction(MainWindowClass);
        actionTile->setObjectName(QStringLiteral("actionTile"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\345\271\263\351\223\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTile->setIcon(icon8);
        actionCascade = new QAction(MainWindowClass);
        actionCascade->setObjectName(QStringLiteral("actionCascade"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\345\261\202\345\217\240.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCascade->setIcon(icon9);
        actionNext = new QAction(MainWindowClass);
        actionNext->setObjectName(QStringLiteral("actionNext"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\344\270\213\345\274\240.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext->setIcon(icon10);
        actionPrevious = new QAction(MainWindowClass);
        actionPrevious->setObjectName(QStringLiteral("actionPrevious"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\344\270\212\345\274\240.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious->setIcon(icon11);
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("../../../../../\345\233\276\346\240\207-\347\275\221\344\270\212\344\270\213\350\275\275/\345\233\276\346\240\2072-alibba/\351\227\256\351\242\230.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon12);
        actionAboutQt = new QAction(MainWindowClass);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1046, 26));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_E = new QMenu(menuBar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        menu_W = new QMenu(menuBar);
        menu_W->setObjectName(QStringLiteral("menu_W"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_E->menuAction());
        menuBar->addAction(menu_W->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(actionNew);
        menu_F->addAction(actionOpen);
        menu_F->addAction(actionSave);
        menu_F->addAction(actionSaveAs);
        menu_F->addAction(actionExit);
        menu_F->addSeparator();
        menu_E->addAction(actionUndo);
        menu_E->addAction(actionRedo);
        menu_E->addAction(actionCut);
        menu_E->addAction(actionCopy);
        menu_E->addAction(actionPaste);
        menu_W->addAction(actionClose);
        menu_W->addAction(actionCloseAll);
        menu_W->addAction(actionTile);
        menu_W->addAction(actionCascade);
        menu_W->addAction(actionNext);
        menu_W->addAction(actionPrevious);
        menu_H->addAction(actionAbout);
        menu_H->addAction(actionAboutQt);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSaveAs);
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionPrevious);
        mainToolBar->addAction(actionNext);
        mainToolBar->addAction(actionTile);
        mainToolBar->addAction(actionCascade);
        mainToolBar->addAction(actionCloseAll);
        mainToolBar->addAction(actionAbout);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272\346\226\207\344\273\266(N)", 0));
        actionNew->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\346\226\207\344\273\266(O)", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230\346\226\207\344\273\266(S)", 0));
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0));
        actionSaveAs->setText(QApplication::translate("MainWindowClass", "\345\217\246\345\255\230\344\270\272(A)", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272(X)", 0));
        actionUndo->setText(QApplication::translate("MainWindowClass", "\346\222\244\351\224\200(U)", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindowClass", "\346\201\242\345\244\215(R)", 0));
        actionCut->setText(QApplication::translate("MainWindowClass", "\345\211\252\345\210\207(T)", 0));
        actionCut->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+X", 0));
        actionCopy->setText(QApplication::translate("MainWindowClass", "\345\244\215\345\210\266(C)", 0));
        actionCopy->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+C", 0));
        actionPaste->setText(QApplication::translate("MainWindowClass", "\347\262\230\350\264\264(P)", 0));
        actionPaste->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+V", 0));
        actionClose->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255(O)", 0));
        actionCloseAll->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255\346\211\200\346\234\211(A)", 0));
        actionTile->setText(QApplication::translate("MainWindowClass", "\345\271\263\351\223\272\346\230\276\347\244\272(T)", 0));
        actionCascade->setText(QApplication::translate("MainWindowClass", "\345\261\202\345\217\240\346\230\276\347\244\272(C)", 0));
        actionNext->setText(QApplication::translate("MainWindowClass", "\344\270\213\344\270\200\344\270\252(X)", 0));
        actionPrevious->setText(QApplication::translate("MainWindowClass", "\345\211\215\344\270\200\344\270\252(V)", 0));
        actionAbout->setText(QApplication::translate("MainWindowClass", "\345\205\263\344\272\216(A)", 0));
        actionAboutQt->setText(QApplication::translate("MainWindowClass", "\345\205\263\344\272\216Qt(Q)", 0));
        menu_F->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(&F)", 0));
        menu_E->setTitle(QApplication::translate("MainWindowClass", "\347\274\226\350\276\221(E)", 0));
        menu_W->setTitle(QApplication::translate("MainWindowClass", "\347\252\227\345\217\243(W)", 0));
        menu_H->setTitle(QApplication::translate("MainWindowClass", "\345\270\256\345\212\251(H)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
