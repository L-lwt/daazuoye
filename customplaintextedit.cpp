#include "customplaintextedit.h"
#include <QRegularExpression>
#include <QDesktopServices>
#include <QUrl>

CustomPlainTextEdit::CustomPlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
}

void CustomPlainTextEdit::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//查是否是鼠标左键被点击
    {
        QTextCursor cursor = cursorForPosition(event->pos());//QTextCursor cursor = cursorForPosition(event->pos());

        QString text = toPlainText();//文本编辑器中的所有文本

        // 则表达式匹配URL和电子邮件地址s
        QRegularExpression regex(R"((http|https|ftp):\/\/[^\s/$.?#].[^\s]*|mailto:\S+)");
        auto matches = regex.globalMatch(text);
        //遍历所有匹配项
        while (matches.hasNext())
        {
            auto match = matches.next();
            int start = match.capturedStart();
            int end = match.capturedEnd();

            if (cursor.position() >= start && cursor.position() <= end)
            {
                QUrl url(match.captured());
                QDesktopServices::openUrl(url);
                break;
            }
        }
    }

    QPlainTextEdit::mousePressEvent(event);//这行代码调用基类QPlainTextEdit的mousePressEvent函数，确保其他鼠标点击事件被正常处理
}
