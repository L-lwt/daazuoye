#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QColorDialog>
#include <QPlainTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow //MainWindow类继承自QMainWindow类
{
    Q_OBJECT  //Q_OBJECT是一个宏（macro），在Qt框架中用于支持Qt的元对象系统（Meta-Object System）。这是一个非常重要的宏，用于在Qt类中启用某些功能，比如信号和槽（signals and slots）、属性（properties）、以及类信息（class information）

public:
    MainWindow(QWidget *parent = nullptr);//nullptr是空指针
    ~MainWindow();//析构函数的声明

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveas_triggered();
    void on_textEdit_textChanged();
    void on_actionExit_triggered();
    void on_actionbackcolor_triggered();
    void closeTab(void);
private:
    Ui::MainWindow *ui;
   // QLabel statusCursorLabel;
    //QLabel statusLabel;
    QString filePath;
    bool textChanged;
    bool textEditConfirmed();
    int i=1;
    QTabWidget *tabWidget;
    QMap<QPlainTextEdit*, QString> filePaths; //用于存储键值对,它将QTextEdit指针作为键，将QString作为值
};
#endif // MAINWINDOW_H
