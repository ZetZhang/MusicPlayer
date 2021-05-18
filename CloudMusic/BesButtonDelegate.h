﻿#ifndef BES_BUTTON_DELEGATE_H
#define BES_BUTTON_DELEGATE_H

#include <QPushButton>
#include <BesButton.h>
#include <QStyledItemDelegate>

class BesButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BesButtonDelegate(QObject *parent = 0);
    void init_btnStyle();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void sig_rowClicked(int row);
    void sig_preview_ncm_song(int row);
    void sig_listen_ncm_song(int row);
    void sig_download_ncm_song(int row);
    void sig_search_ncm_lyric(int row);
//    void sig_setMusicPathToMakingPage(QString);

private:
    QPoint m_mousePoint;  // 鼠标位置
    QScopedPointer<BesButton> m_pBtnPreviewSong;
    QScopedPointer<BesButton> m_pBtnListenSong;
    QScopedPointer<BesButton> m_pBtnDownloadSong;
    QScopedPointer<BesButton> m_pBtnDownloadLyric;
    QStringList m_list;
    int m_nSpacing;  // 按钮之间的间距
    int m_nWidth;  // 按钮宽度
    int m_nHeight;  // 按钮高度
    int m_nType;  // 按钮状态-1：划过 2：按下
};

#endif // BES_NCM_SONG_BUTTON_DELEGATE_H
