#ifndef FAVORITESMANAGER_H
#define FAVORITESMANAGER_H

#include <QObject>
#include <QStringListModel>

class FavoritesManager : public QObject
{
    Q_OBJECT

public:
    explicit FavoritesManager(QObject *parent = nullptr);

    QStringListModel* model() const;
    void addFavorite(const QString &path);
    void removeFavorite(const QString &path);

private:
    QStringListModel *m_model;
};

#endif // FAVORITESMANAGER_H
