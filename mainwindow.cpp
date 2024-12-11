#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textChanged=false;

    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
     statusLabel.setMaximumWidth(150);
     statusLabel.setText("Length: " + QString::number(0) + " lines: " + QString::number(1));
     ui->statusbar->addPermanentWidget(&statusLabel);

     statusCursorLabel.setMaximumWidth(150);
     statusCursorLabel.setText("Ln: " + QString::number(0) + " Col: " + QString::number(1));
     ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("林文涛"));
    ui->statusbar->addPermanentWidget(author);

    connect(ui->actionC, &QAction::triggered, this, &MainWindow::setLanguageC);
    connect(ui->actionPython, &QAction::triggered, this, &MainWindow::setLanguagePython);
    connect(ui->actionJavaScript, &QAction::triggered, this, &MainWindow::setLanguageJavaScript);
    connect(ui->actionHTML, &QAction::triggered, this, &MainWindow::setLanguageHTML);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    // 创建新的 QTextEdit 组件
    QPlainTextEdit *editor = new QPlainTextEdit(this);
    // 添加到 QTabWidget 中
    QString tabName = QString("未命名-%1").arg(i); // 将变量i插入到字符串中
    int index = tabWidget->addTab(editor, tabName); // 添加标签
    tabWidget->setCurrentIndex(index);
    i++;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "", tr("文本文件 (*.txt)"));
    if (!fileName.isEmpty()) {
        // 读取文件内容
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {//只读模式打开文件,以文本模式打开文件
            QTextStream in(&file);
            QString text = in.readAll();
            file.close();

            // 创建新的 QTextEdit 组件
            QPlainTextEdit *editor = new QPlainTextEdit(this);
            editor->setPlainText(text);

            // 添加到 QTabWidget 中
            int index = tabWidget->addTab(editor, QFileInfo(fileName).fileName());
            // 设置当前标签页
            tabWidget->setCurrentIndex(index);
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    // 获取当前活动的 QPlainTextEdit 组件
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    if (!currentEditor) return; // 如果没有当前活动的编辑器，则退出

    // 检查是否有已记录的文件路径
    bool isNewFile = !filePaths.contains(currentEditor);
    QString filePath = isNewFile ? "" : filePaths[currentEditor];

    // 如果是新文件或有未保存更改，则执行保存操作
    if (isNewFile || currentEditor->document()->isModified()) {
        QString fileName;
        if (isNewFile) { // 对于新文件，必须选择保存位置
            fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("文本文件 (*.txt)"));//filename是路径，当用户使用对话框选择文件路径和名称后，getSaveFileName() 函数会返回用户选择的完整文件路径。如果用户取消了保存操作，则返回一个空字符串
            if (fileName.isEmpty()) {
                return; // 用户取消了保存操作
            }
            filePaths[currentEditor] = fileName; // 记录文件路径
        } else {
            fileName = filePath;
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << currentEditor->toPlainText();
            file.close();
            currentEditor->document()->setModified(false); // 保存后重置修改状态

            // 更新标签页标题，移除星号标记
            int index = tabWidget->indexOf(currentEditor);
            if (index != -1) {
                QString title = QFileInfo(fileName).fileName();
                tabWidget->setTabText(index, title);
            }//这行代码使用 QFileInfo 类获取文件名。QFileInfo 的 fileName() 方法返回文件的基本名称（不包含路径）。fileName 是之前保存文件时指定的文件路径。

            QMessageBox::information(this, tr("保存成功"), tr("文件已成功保存。"));
        } else {
            QMessageBox::warning(this, tr("保存失败"), tr("无法保存文件 %1").arg(fileName));
        }
    } else {
        // 文件未修改，不需要保存
        QMessageBox::information(this, tr("无需保存"), tr("文件没有修改，无需保存。"));
    }

}


void MainWindow::on_actionSaveas_triggered()
{
    // 获取当前活动的 QTextEdit 组件
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    if (!currentEditor) return; // 如果没有当前活动的编辑器，则退出

    // 提示用户选择保存位置
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("文本文件 (*.txt)"));
    if (fileName.isEmpty()) {
        return; // 用户取消了保存操作
    }

    // 保存文件到新位置
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << currentEditor->toPlainText();
        file.close();

        // 更新文件路径映射
        filePaths[currentEditor] = fileName;
        currentEditor->document()->setModified(false); // 保存后重置修改状态

        // 更新标签页标题，移除星号标记
        int index = tabWidget->indexOf(currentEditor);
        if (index != -1) {
            QString title = QFileInfo(fileName).fileName();
            tabWidget->setTabText(index, title);
        }

        QMessageBox::information(this, tr("保存成功"), tr("文件已成功保存到新位置。"));
    } else {
        QMessageBox::warning(this, tr("保存失败"), tr("无法保存文件 %1").arg(fileName));
    }
}


void MainWindow::on_textEdit_textChanged()
{
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    if(!textChanged){
        this->setWindowTitle("*"+this->windowTitle());
        textChanged=true;
    }
    statusLabel.setText("length: " + QString::number(currentEditor->toPlainText().length()) +
                        " lines: " +
                        QString::number(currentEditor->document()->lineCount()));

}

bool MainWindow::textEditConfirmed()
{
    if(textChanged){
        QString path = (filePath !="")? filePath : "无标题.txt";
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n")+"\""+path+"\"?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int r = msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;

}


void MainWindow::on_actionExit_triggered()
{
    bool canExit = true;

    for (int i = 0; i < tabWidget->count(); ++i) {
        QPlainTextEdit *editor = qobject_cast<QPlainTextEdit*>(tabWidget->widget(i));
        if (!editor || !editor->document()->isModified()) continue;

        // 文件有未保存的更改，提示用户选择如何处理
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("保存更改"),
                                                                   tr("文档已修改。\n您希望保存更改吗？"),
                                                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                                   QMessageBox::Save);
        if (resBtn == QMessageBox::Save) {
            // 尝试保存文件
            QString filePath = filePaths.value(editor);
            bool isNewFile = filePath.isEmpty();

            QString fileName;
            if (isNewFile) { // 对于新文件，必须选择保存位置
                fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("文本文件 (*.txt)"));
                if (fileName.isEmpty()) {
                    canExit = false;
                    break; // 用户取消了保存操作
                }
                filePaths[editor] = fileName; // 记录文件路径
            } else {
                fileName = filePath;
            }

            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << editor->toPlainText();
                file.close();
                editor->document()->setModified(false); // 保存后重置修改状态

                // 更新标签页标题，移除星号标记
                int index = tabWidget->indexOf(editor);
                if (index != -1) {
                    QString title = QFileInfo(fileName).fileName();
                    tabWidget->setTabText(index, title);
                }
            } else {
                QMessageBox::warning(this, tr("保存失败"), tr("无法保存文件 %1").arg(fileName));
                canExit = false;
                break;
            }
        } else if (resBtn == QMessageBox::Cancel) {
            // 用户选择取消，停止退出流程
            return;
        }
        // 如果选择了 Discard，则继续尝试关闭其他文件
    }

    if (canExit) {
        // 所有文件都已处理完毕，允许关闭应用程序
        QApplication::quit();
    }
}


void MainWindow::on_actionbackcolor_triggered()
{
    // 获取当前活动的 QTextEdit 组件
    QTextEdit *currentEditor = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!currentEditor) return; // 如果没有当前活动的编辑器，则退出

    // 弹出颜色选择对话框
    QColor color = QColorDialog::getColor(Qt::white, this, tr("选择背景颜色"));

    // 如果用户选择了颜色且不是默认的 invalid 颜色
    if (color.isValid()) {
        QPalette p = currentEditor->palette();
        p.setColor(QPalette::Base, color);
        currentEditor->setPalette(p);
    }
}

void MainWindow::closeTab()
{
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    if (!currentEditor) return; // 如果没有当前活动的编辑器，则退出

    // 检查是否有已记录的文件路径
    bool isNewFile = !filePaths.contains(currentEditor);
    QString filePath = isNewFile ? "" : filePaths[currentEditor];

    // 如果是新文件或有未保存更改，则执行保存操作
    if (isNewFile || currentEditor->document()->isModified()) {
        QString fileName;
        if (isNewFile) { // 对于新文件，必须选择保存位置
            fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("文本文件 (*.txt)"));//filename是路径，当用户使用对话框选择文件路径和名称后，getSaveFileName() 函数会返回用户选择的完整文件路径。如果用户取消了保存操作，则返回一个空字符串
            if (fileName.isEmpty()) {
                return; // 用户取消了保存操作
            }
            filePaths[currentEditor] = fileName; // 记录文件路径
        } else {
            fileName = filePath;
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << currentEditor->toPlainText();
            file.close();
            currentEditor->document()->setModified(false); // 保存后重置修改状态

            // 更新标签页标题，移除星号标记
            int index = tabWidget->indexOf(currentEditor);
            if (index != -1) {
                QString title = QFileInfo(fileName).fileName();
                tabWidget->setTabText(index, title);
            }//这行代码使用 QFileInfo 类获取文件名。QFileInfo 的 fileName() 方法返回文件的基本名称（不包含路径）。fileName 是之前保存文件时指定的文件路径。

            QMessageBox::information(this, tr("保存成功"), tr("文件已成功保存。"));
        } else {
            QMessageBox::warning(this, tr("保存失败"), tr("无法保存文件 %1").arg(fileName));
        }
    } else {
        // 文件未修改，不需要保存
        QMessageBox::information(this, tr("无需保存"), tr("文件没有修改，无需保存。"));
    }
    int index=tabWidget->currentIndex();
    tabWidget->removeTab(index);
}

void MainWindow::setLanguageC() {
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    highlighter = new Highlighter(currentEditor->document(), "C");
}

void MainWindow::setLanguagePython() {
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    highlighter = new Highlighter(currentEditor->document(), "Python");
}

void MainWindow::setLanguageJavaScript() {
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    highlighter = new Highlighter(currentEditor->document(), "JavaScript");
}

void MainWindow::setLanguageHTML() {
    QPlainTextEdit *currentEditor = qobject_cast<QPlainTextEdit*>(tabWidget->currentWidget());
    highlighter = new Highlighter(currentEditor->document(), "HTML");
}

