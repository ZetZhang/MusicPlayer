#ifndef THREADSEARCH_NCM_MUSIC_H
#define THREADSEARCH_NCM_MUSIC_H

#include "SongSearchResult.h"
#include "SearcherNetEaseCloud.h"

#include <QMutex>
#include <QThread>
#include <QObject>
#include <QMessageBox>
#include <QMutexLocker>
#include <QSharedPointer>

class ThreadSearchNcmMusic : public QThread
{
    Q_OBJECT

public:
    ThreadSearchNcmMusic() : m_bIsSearching(false) {  }

    void StartSearchNcm(QString artist, QString song) {
        QMutexLocker locker(&mutex);

        if(m_bIsSearching) {
            QMessageBox::about(nullptr, "等待提示", "搜索模块正被占用，请等待......");
            return;
        }

        m_strArtist = artist;
        m_strSong   = song;

        start(HighestPriority); // 执行线程
    }

signals:
    void songResultChanged(SongSearchResult);  //搜索消息结果改变

protected:
    virtual void run() {
        QString strArtist;
        QString strSong;

        {
           QMutexLocker locker(&mutex);
           m_bIsSearching = true; //进入搜索状态

           strArtist = m_strArtist;
           strSong   = m_strSong;
        }

        QString strResultTip;
        QVector <SONGINFO> vecSongList;

        bool bRet = SearcherNetEaseCloud::GetSongListWithNameAndArtist(strSong, strArtist, vecSongList, strResultTip);

        // 使用 SongSearchResult 发送，由于 SongSearchResult 已经使用 qRegisterMetaType<SongSearchResult>("SongSearchResult");
        // 注册过，可以作为信号参数了，这里直接复用这个结构
        SongSearchResult SearchResult;
        SearchResult.bCurrentSearchDone       = true;        //标记搜索结束
        SearchResult.bAppendToList            = false;       //本线程专门搜索网易云音乐，所以只搜索一次，每次都需要清空列表
        SearchResult.vecSongInfo              = vecSongList;
        SearchResult.bShowUnexpectedResultTip = !bRet;       //是否显示异常信息(即出错)
        SearchResult.strUnexpectedResultTip   = strResultTip;//异常信息

        emit songResultChanged(SearchResult);

        {
           QMutexLocker locker(&mutex);
           m_bIsSearching = false; //退出搜索状态
        }
    }

    QMutex mutex;
    bool m_bIsSearching;
    QString m_strArtist;
    QString m_strSong;
};


#endif // THREADSEARCH_NCM_MUSIC_H
