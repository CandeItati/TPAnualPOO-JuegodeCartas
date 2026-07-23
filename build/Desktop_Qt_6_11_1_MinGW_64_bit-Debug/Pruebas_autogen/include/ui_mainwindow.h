/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblTitulo;
    QLabel *lbljugador;
    QLabel *lblIA;
    QPushButton *PBelemento1;
    QPushButton *PBelemento2;
    QPushButton *PBelemento3;
    QPushButton *PBelemento4;
    QPushButton *PBelemento5;
    QLabel *lbleleJHVida1;
    QLabel *lbleleJHVida2;
    QLabel *lbleleJHVida3;
    QLabel *lbleleJHVida4;
    QLabel *lbleleJHVida5;
    QLabel *lbleleIAVida2;
    QLabel *lbleleIAVida3;
    QLabel *lbleleIAVida4;
    QLabel *lbleleIAVida5;
    QLabel *lbleleIAVida1;
    QLabel *lblTurno;
    QLabel *lblEnfrentamiento;
    QPushButton *btnAtacar;
    QPushButton *btnCambiar;
    QLabel *lblEstado;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lblTitulo = new QLabel(centralwidget);
        lblTitulo->setObjectName("lblTitulo");
        lblTitulo->setGeometry(QRect(200, 0, 381, 111));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lbljugador = new QLabel(centralwidget);
        lbljugador->setObjectName("lbljugador");
        lbljugador->setGeometry(QRect(60, 110, 91, 41));
        lblIA = new QLabel(centralwidget);
        lblIA->setObjectName("lblIA");
        lblIA->setGeometry(QRect(420, 110, 91, 41));
        PBelemento1 = new QPushButton(centralwidget);
        PBelemento1->setObjectName("PBelemento1");
        PBelemento1->setGeometry(QRect(70, 380, 90, 141));
        PBelemento2 = new QPushButton(centralwidget);
        PBelemento2->setObjectName("PBelemento2");
        PBelemento2->setGeometry(QRect(200, 380, 90, 141));
        PBelemento3 = new QPushButton(centralwidget);
        PBelemento3->setObjectName("PBelemento3");
        PBelemento3->setGeometry(QRect(340, 380, 90, 141));
        PBelemento4 = new QPushButton(centralwidget);
        PBelemento4->setObjectName("PBelemento4");
        PBelemento4->setGeometry(QRect(480, 380, 90, 141));
        PBelemento5 = new QPushButton(centralwidget);
        PBelemento5->setObjectName("PBelemento5");
        PBelemento5->setGeometry(QRect(620, 380, 90, 141));
        PBelemento5->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        lbleleJHVida1 = new QLabel(centralwidget);
        lbleleJHVida1->setObjectName("lbleleJHVida1");
        lbleleJHVida1->setGeometry(QRect(170, 120, 131, 20));
        lbleleJHVida2 = new QLabel(centralwidget);
        lbleleJHVida2->setObjectName("lbleleJHVida2");
        lbleleJHVida2->setGeometry(QRect(170, 150, 131, 20));
        lbleleJHVida3 = new QLabel(centralwidget);
        lbleleJHVida3->setObjectName("lbleleJHVida3");
        lbleleJHVida3->setGeometry(QRect(170, 180, 131, 20));
        lbleleJHVida4 = new QLabel(centralwidget);
        lbleleJHVida4->setObjectName("lbleleJHVida4");
        lbleleJHVida4->setGeometry(QRect(170, 210, 131, 20));
        lbleleJHVida5 = new QLabel(centralwidget);
        lbleleJHVida5->setObjectName("lbleleJHVida5");
        lbleleJHVida5->setGeometry(QRect(170, 240, 131, 20));
        lbleleIAVida2 = new QLabel(centralwidget);
        lbleleIAVida2->setObjectName("lbleleIAVida2");
        lbleleIAVida2->setGeometry(QRect(500, 150, 131, 20));
        lbleleIAVida3 = new QLabel(centralwidget);
        lbleleIAVida3->setObjectName("lbleleIAVida3");
        lbleleIAVida3->setGeometry(QRect(500, 180, 131, 20));
        lbleleIAVida4 = new QLabel(centralwidget);
        lbleleIAVida4->setObjectName("lbleleIAVida4");
        lbleleIAVida4->setGeometry(QRect(500, 210, 131, 20));
        lbleleIAVida5 = new QLabel(centralwidget);
        lbleleIAVida5->setObjectName("lbleleIAVida5");
        lbleleIAVida5->setGeometry(QRect(500, 240, 131, 20));
        lbleleIAVida1 = new QLabel(centralwidget);
        lbleleIAVida1->setObjectName("lbleleIAVida1");
        lbleleIAVida1->setGeometry(QRect(500, 120, 131, 20));
        lblTurno = new QLabel(centralwidget);
        lblTurno->setObjectName("lblTurno");
        lblTurno->setGeometry(QRect(70, 280, 481, 20));
        lblEnfrentamiento = new QLabel(centralwidget);
        lblEnfrentamiento->setObjectName("lblEnfrentamiento");
        lblEnfrentamiento->setGeometry(QRect(330, 280, 391, 20));
        btnAtacar = new QPushButton(centralwidget);
        btnAtacar->setObjectName("btnAtacar");
        btnAtacar->setGeometry(QRect(120, 410, 251, 91));
        btnCambiar = new QPushButton(centralwidget);
        btnCambiar->setObjectName("btnCambiar");
        btnCambiar->setGeometry(QRect(400, 410, 251, 91));
        lblEstado = new QLabel(centralwidget);
        lblEstado->setObjectName("lblEstado");
        lblEstado->setGeometry(QRect(200, 320, 381, 31));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        lblEstado->setFont(font1);
        lblEstado->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblTitulo->setText(QCoreApplication::translate("MainWindow", "COMBATE ELEMENTAL", nullptr));
        lbljugador->setText(QCoreApplication::translate("MainWindow", "JUGADOR:", nullptr));
        lblIA->setText(QCoreApplication::translate("MainWindow", "IA:", nullptr));
        PBelemento1->setText(QCoreApplication::translate("MainWindow", "Elemento1", nullptr));
        PBelemento2->setText(QCoreApplication::translate("MainWindow", "Elemento2", nullptr));
        PBelemento3->setText(QCoreApplication::translate("MainWindow", "Elemento3", nullptr));
        PBelemento4->setText(QCoreApplication::translate("MainWindow", "Elemento4", nullptr));
        PBelemento5->setText(QCoreApplication::translate("MainWindow", "Elemento5", nullptr));
        lbleleJHVida1->setText(QCoreApplication::translate("MainWindow", "Elemento1: 100%", nullptr));
        lbleleJHVida2->setText(QCoreApplication::translate("MainWindow", "Elemento2: 100%", nullptr));
        lbleleJHVida3->setText(QCoreApplication::translate("MainWindow", "Elemento3: 100%", nullptr));
        lbleleJHVida4->setText(QCoreApplication::translate("MainWindow", "Elemento4: 100%", nullptr));
        lbleleJHVida5->setText(QCoreApplication::translate("MainWindow", "Elemento5: 100%", nullptr));
        lbleleIAVida2->setText(QCoreApplication::translate("MainWindow", "Elemento2: 100%", nullptr));
        lbleleIAVida3->setText(QCoreApplication::translate("MainWindow", "Elemento3: 100%", nullptr));
        lbleleIAVida4->setText(QCoreApplication::translate("MainWindow", "Elemento4: 100%", nullptr));
        lbleleIAVida5->setText(QCoreApplication::translate("MainWindow", "Elemento5: 100%", nullptr));
        lbleleIAVida1->setText(QCoreApplication::translate("MainWindow", "Elemento1: 100%", nullptr));
        lblTurno->setText(QCoreApplication::translate("MainWindow", "TURNO ACTUAL:   JUGADOR", nullptr));
        lblEnfrentamiento->setText(QCoreApplication::translate("MainWindow", "ENFRENTAMIENTO: ------------------ VS -------------------", nullptr));
        btnAtacar->setText(QCoreApplication::translate("MainWindow", "ATACAR", nullptr));
        btnCambiar->setText(QCoreApplication::translate("MainWindow", "CAMBIAR ELEMENTO", nullptr));
        lblEstado->setText(QCoreApplication::translate("MainWindow", "Selecione un elemento", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
