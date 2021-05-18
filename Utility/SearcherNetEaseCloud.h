#pragma once
#ifndef SEARCHERNETEASECLOUD_H
#define SEARCHERNETEASECLOUD_H

#include "SongSearchResult.h"

#include <QObject>
#include <QVector>
#include <QString>

class ISearcher
{
public:
    /*
        @brief	搜索歌词
        @param	strSong			搜索的歌曲名
        @param	strArtist		搜索的歌手
        @param	vecLyricInfo	获得的歌词数据
        @return	false —— 网络连接异常 或 数据格式出错
        @note	注意该函数需要将操作的结果写入 m_strLastResult，
    */
    virtual bool SearchLyric(QVector<SONGINFO> vecSongList, QVector<LyricInfo>& vecLyricInfo) = 0;
    virtual bool SearchLyric(SONGINFO info, LyricInfo& vecLyricInfo) = 0;

    virtual QString GetLastResult()
    {
        return  m_strLastResult;
    }

    virtual ~ISearcher(){}
protected:
    QString m_strLastResult;
};


class SearcherNetEaseCloud : public QObject, public ISearcher
{
public:
    virtual ~SearcherNetEaseCloud(){}

    //搜索歌词
    virtual bool SearchLyric(QVector<SONGINFO> vecSongList, QVector<LyricInfo>& vecLyricInfo);
    virtual bool SearchLyric(SONGINFO info, LyricInfo& vecLyricInfo);
    //通过使用歌名 和 艺术家名获得 歌曲信息列表
    static bool GetSongListWithNameAndArtist(QString strSong, QString strArtist, QVector<SONGINFO> &vecSongList, QString &strLastResult);
    //获得结果中的歌曲信息列表
    static bool GetSongListFromJson(QString strJsonRes, QVector<SONGINFO> &vecSongList);

private:

    //从单个歌词json数据获得歌词
    bool GetOneLyricFromJson(QString strLyricJson,  LyricInfo& oneLyricInfo);
    //从歌词文本缓存获取 歌词 信息
    void GetOneLyricInfoFromLyricBuffer(QString strLyricBuffer,LyricInfo& lyricInfo);
};

#endif // SEARCHERNETEASECLOUD_H
