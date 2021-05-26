#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_Open_File_1_clicked();

    void on_Button_Open_File_2_clicked();

    void on_Button_Start_clicked();

private:
    Ui::MainWindow *ui;
    void UpdateTable(QList<int> metrics_1, QList<int> metrics_2);
    void CalulateResult(QList<int> metrics_1, QList<int> metrics_2);

};

#endif // MAINWINDOW_H
