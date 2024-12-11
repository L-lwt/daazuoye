#include "recentfiles.h"
#include <QSettings>

RecentFiles::RecentFiles() {
    loadHistory();//构造函数中调用 loadHistory() 函数
}

void RecentFiles::addFile(const QString &fileName) {
    history.removeAll(fileName); //从历史记录中删除所有已有的相同文件名，确保同一个文件不会重复出现在历史记录中。
    history.prepend(fileName); // 将新的文件名添加到历史记录的前面，使其成为最近使用的文件。
    if (history.size() > maxHistorySize) {
        history.removeLast(); //  如果超出限制，删除最旧的条目
    }
    QSettings settings("东莞理工学院", "记事本");
    settings.setValue("recentFiles", history);
}

void RecentFiles::clearHistory() {
    history.clear();
    QSettings settings("东莞理工学院", "记事本");
    settings.setValue("recentFiles", history);
}

QStringList RecentFiles::getHistory() const {
    return history;
}

void RecentFiles::loadHistory() {
    QSettings settings("东莞理工学院", "记事本");
    history = settings.value("recentFiles").toStringList();
}
