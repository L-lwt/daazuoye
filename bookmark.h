#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QString>

class Bookmark
{
public:
    Bookmark(int line, const QString &text);

    int line() const;
    QString text() const;

private:
    int m_line;
    QString m_text;
};

#endif // BOOKMARK_H
