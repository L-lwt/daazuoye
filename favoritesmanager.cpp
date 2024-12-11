#include "favoritesmanager.h"

FavoritesManager::FavoritesManager(QObject *parent) :
    QObject(parent),
    m_model(new QStringListModel(this))
{
}

QStringListModel* FavoritesManager::model() const
{
    return m_model;
}

void FavoritesManager::addFavorite(const QString &path)
{
    QStringList list = m_model->stringList();
    if (!list.contains(path)) {
        list.append(path);
        m_model->setStringList(list);
    }
}

void FavoritesManager::removeFavorite(const QString &path)
{
    QStringList list = m_model->stringList();
    list.removeAll(path);
    m_model->setStringList(list);
}
