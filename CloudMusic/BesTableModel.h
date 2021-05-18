#ifndef BES_TABLE_MODEL_H
#define BES_TABLE_MODEL_H

#include "SongSearchResult.h"

#include <QVector>
#include <QAbstractTableModel>

class BesTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BesTableModel(QObject *parent = 0);
    ~BesTableModel(void);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setHorizontalHeader(const QStringList& headers);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setData(const QVector<SONGINFO>& data);
    QVector<SONGINFO>& DataVector() { return m_data; }

    void deleteAllItems();
    void appendItems(const QVector<SONGINFO>& infos);

private:
    QStringList m_HorizontalHeader;
    QVector<SONGINFO> m_data;
};

#endif // BES_NCM_SONG_TABLE_MODEL_H
