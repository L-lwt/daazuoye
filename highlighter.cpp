#include "highlighter.h"
//:: 是作用域解析运算符（Scope Resolution Operator）。它用于访问类、结构体、命名空间或枚举中的成员
Highlighter::Highlighter(QTextDocument *parent, const QString &language)//这是 Highlighter 类的构造函数，位于类的外部定义。前面的 Highlighter:: 表示这是 Highlighter 类的成员函数
    : QSyntaxHighlighter(parent), currentLanguage(language) {
    if (language == "C") {
        setupCLanguage();
    } else if (language == "Python") {
        setupPythonLanguage();
    } else if (language == "JavaScript") {
        setupJavaScriptLanguage();
    } else if (language == "HTML") {
        setupHTMLLanguage();
    }
}

//用于对文本块进行语法高亮处理
void Highlighter::highlightBlock(const QString &text) {
    for (const auto &pattern : keywordPatterns) {
        QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), keywordFormat);
        }
    }

    // Highlight single-line comments
    QRegularExpression singleLineCommentPattern("//[^\n]*");
    QRegularExpressionMatchIterator singleLineCommentIterator = singleLineCommentPattern.globalMatch(text);
    while (singleLineCommentIterator.hasNext()) {
        QRegularExpressionMatch match = singleLineCommentIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), singleLineCommentFormat);
    }

    // Highlight multi-line comments
    QRegularExpression multiLineCommentStartPattern("/\\*");
    QRegularExpression multiLineCommentEndPattern("\\*/");
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = multiLineCommentStartPattern.match(text).capturedStart();
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch = multiLineCommentEndPattern.match(text, startIndex);
        int endIndex = endMatch.capturedEnd();
        int commentLength = 0;
        if (endMatch.hasMatch()) {
            commentLength = endIndex - startIndex;
            setCurrentBlockState(0);
        } else {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = multiLineCommentStartPattern.match(text, startIndex + commentLength).capturedStart();
    }

    // Highlight strings
    QRegularExpression stringPattern("\".*\"|'[^']*'");
    QRegularExpressionMatchIterator stringIterator = stringPattern.globalMatch(text);
    while (stringIterator.hasNext()) {
        QRegularExpressionMatch match = stringIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), stringFormat);
    }

    // Highlight functions
    QRegularExpression functionPattern("\\b[A-Za-z0-9_]+(?=\\()");
    QRegularExpressionMatchIterator functionIterator = functionPattern.globalMatch(text);
    while (functionIterator.hasNext()) {
        QRegularExpressionMatch match = functionIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), functionFormat);
    }

    // Highlight numbers
    QRegularExpression numberPattern("\\b\\d+\\b");
    QRegularExpressionMatchIterator numberIterator = numberPattern.globalMatch(text);
    while (numberIterator.hasNext()) {
        QRegularExpressionMatch match = numberIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), numberFormat);
    }

    // Highlight operators
    QRegularExpression operatorPattern("[+\\-*/%&|^!<>=]=?|\\b(and|or|not)\\b");
    QRegularExpressionMatchIterator operatorIterator = operatorPattern.globalMatch(text);
    while (operatorIterator.hasNext()) {
        QRegularExpressionMatch match = operatorIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), operatorFormat);
    }
}

void Highlighter::setupCLanguage() {
    keywordPatterns << QRegularExpression("\\bchar\\b")
    << QRegularExpression("\\bclass\\b")
    << QRegularExpression("\\bconst\\b")
    << QRegularExpression("\\bdouble\\b")
    << QRegularExpression("\\benum\\b")
    << QRegularExpression("\\bexplicit\\b")
    << QRegularExpression("\\bfriend\\b")
    << QRegularExpression("\\binline\\b")
    << QRegularExpression("\\bint\\b")
    << QRegularExpression("\\blong\\b")
    << QRegularExpression("\\bnamespace\\b")
    << QRegularExpression("\\boperator\\b")
    << QRegularExpression("\\bprivate\\b")
    << QRegularExpression("\\bprotected\\b")
    << QRegularExpression("\\bpublic\\b")
    << QRegularExpression("\\bshort\\b")
    << QRegularExpression("\\bsignals\\b")
    << QRegularExpression("\\bsigned\\b")
    << QRegularExpression("\\bslots\\b")
    << QRegularExpression("\\bstatic\\b")
    << QRegularExpression("\\bstruct\\b")
    << QRegularExpression("\\btemplate\\b")
    << QRegularExpression("\\btypedef\\b")
    << QRegularExpression("\\btypename\\b")
    << QRegularExpression("\\bunion\\b")
    << QRegularExpression("\\bunsigned\\b")
    << QRegularExpression("\\bvirtual\\b")
    << QRegularExpression("\\bvoid\\b")
    << QRegularExpression("\\bvolatile\\b")
    << QRegularExpression("\\bbool\\b")
    << QRegularExpression("\\bif\\b")
    << QRegularExpression("\\belse\\b")
    << QRegularExpression("\\bwhile\\b")
    << QRegularExpression("\\bfor\\b")
    << QRegularExpression("\\breturn\\b");

    keywordFormat.setForeground(Qt::blue);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontItalic(true);

    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    stringFormat.setForeground(Qt::darkRed);

    functionFormat.setForeground(Qt::darkMagenta);

    numberFormat.setForeground(Qt::darkCyan);

    operatorFormat.setForeground(Qt::darkBlue);
}

void Highlighter::setupPythonLanguage() {
    keywordPatterns << QRegularExpression("\\bdef\\b")
    << QRegularExpression("\\bclass\\b")
    << QRegularExpression("\\bimport\\b")
    << QRegularExpression("\\bfrom\\b")
    << QRegularExpression("\\bas\\b")
    << QRegularExpression("\\bif\\b")
    << QRegularExpression("\\belse\\b")
    << QRegularExpression("\\belif\\b")
    << QRegularExpression("\\bfor\\b")
    << QRegularExpression("\\bwhile\\b")
    << QRegularExpression("\\breturn\\b")
    << QRegularExpression("\\btry\\b")
    << QRegularExpression("\\bexcept\\b")
    << QRegularExpression("\\bfinally\\b")
    << QRegularExpression("\\bwith\\b")
    << QRegularExpression("\\band\\b")
    << QRegularExpression("\\bor\\b")
    << QRegularExpression("\\bnot\\b");

    keywordFormat.setForeground(Qt::blue);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontItalic(true);

    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    stringFormat.setForeground(Qt::darkRed);

    functionFormat.setForeground(Qt::darkMagenta);

    numberFormat.setForeground(Qt::darkCyan);

    operatorFormat.setForeground(Qt::darkBlue);
}

void Highlighter::setupJavaScriptLanguage() {
    keywordPatterns << QRegularExpression("\\bfunction\\b")
    << QRegularExpression("\\bvar\\b")
    << QRegularExpression("\\bconst\\b")
    << QRegularExpression("\\blet\\b")
    << QRegularExpression("\\bif\\b")
    << QRegularExpression("\\belse\\b")
    << QRegularExpression("\\bfor\\b")
    << QRegularExpression("\\bwhile\\b")
    << QRegularExpression("\\breturn\\b")
    << QRegularExpression("\\btry\\b")
    << QRegularExpression("\\bcatch\\b")
    << QRegularExpression("\\bfinally\\b")
    << QRegularExpression("\\btypeof\\b")
    << QRegularExpression("\\bnew\\b")
    << QRegularExpression("\\bthis\\b")
    << QRegularExpression("\\binstanceof\\b")
    << QRegularExpression("\\bnull\\b")
    << QRegularExpression("\\btrue\\b")
    << QRegularExpression("\\bfalse\\b");

    keywordFormat.setForeground(Qt::blue);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontItalic(true);

    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    stringFormat.setForeground(Qt::darkRed);

    functionFormat.setForeground(Qt::darkMagenta);

    numberFormat.setForeground(Qt::darkCyan);

    operatorFormat.setForeground(Qt::darkBlue);
}

void Highlighter::setupHTMLLanguage() {
    keywordPatterns << QRegularExpression("<[^>]+>")
    << QRegularExpression("</[^>]+>")
    << QRegularExpression("\\bclass\\b")
    << QRegularExpression("\\bid\\b")
    << QRegularExpression("\\bstyle\\b")
    << QRegularExpression("\\bsrc\\b")
    << QRegularExpression("\\bhref\\b")
    << QRegularExpression("\\bdata-\\b");

    keywordFormat.setForeground(Qt::blue);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontItalic(true);

    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    stringFormat.setForeground(Qt::darkRed);

    functionFormat.setForeground(Qt::darkMagenta);

    numberFormat.setForeground(Qt::darkCyan);

    operatorFormat.setForeground(Qt::darkBlue);
}
