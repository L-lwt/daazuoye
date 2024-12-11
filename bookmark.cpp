#include "bookmark.h"

// 构造函数
Bookmark::Bookmark(int line, const QString &text)
    : m_line(line), m_text(text)
{
}

// 获取行号
int Bookmark::line() const
{
    return m_line;
}

// 获取文本
QString Bookmark::text() const
{
    return m_text;
}
