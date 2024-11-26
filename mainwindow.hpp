#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "caisse.hpp"
#include<QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QString>
#include <QVariant>
#include <QLineEdit>
#include <QListWidget>
#include <QCheckBox>
#include <QFrame>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    Caisse caisse_;

    QLabel* make_title(std::string title);
    QLabel* make_text(std::string text, Qt::AlignmentFlag align1,Qt::AlignmentFlag align2);
    template<typename T>
    QPushButton* make_button(std::string text, const T& slot);

    void updateList(QListWidget* list, std::vector<Article>& articles);
    void updateLabel(QLabel* label, double number);

};
#endif // MAINWINDOW_H
