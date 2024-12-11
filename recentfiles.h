#ifndef RECENTFILES_H
#define RECENTFILES_H

#include <QStringList>

class RecentFiles {
public:
    RecentFiles();
    void addFile(const QString &fileName);
    void clearHistory();
    QStringList getHistory() const;
    void loadHistory();

private:
    QStringList history;
    const int maxHistorySize = 10;
};

#endif // RECENTFILES_H
