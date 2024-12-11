#ifndef CUSTOMPLAINTEXTEDIT_H
#define CUSTOMPLAINTEXTEDIT_H

#include <QPlainTextEdit>

class CustomPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CustomPlainTextEdit(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CUSTOMPLAINTEXTEDIT_H
