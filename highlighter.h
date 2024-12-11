#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr, const QString &language = "C");

protected:
    void highlightBlock(const QString &text) override;

private:
    void setupCLanguage();
    void setupPythonLanguage();
    void setupJavaScriptLanguage();
    void setupHTMLLanguage();

    QString currentLanguage;
    QVector<QRegularExpression> keywordPatterns;
    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat operatorFormat;
};

#endif // HIGHLIGHTER_H
