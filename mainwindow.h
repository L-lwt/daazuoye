#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QColorDialog>
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
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveas_triggered();

    void on_textEdit_textChanged();

    void on_actionExit_triggered();

    void on_actionbackcolor_triggered();

private:
    Ui::MainWindow *ui;
    QLabel statusCursorLabel;
    QLabel statusLabel;
    QString filePath;
    bool textChanged;
    bool textEditConfirmed();
    int i=1;
    QTabWidget *tabWidget;
     QMap<QTextEdit*, QString> filePaths; // 辅助数据结构，存储文件路径
};
#endif // MAINWINDOW_H
