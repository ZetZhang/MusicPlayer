#ifndef SONGSEARCHRESULT_H
#define SONGSEARCHRESULT_H

#include <QString>
#include <QVector>

/**
 * @brief  音乐保存目录
 */
//static const QString MUSIC_DOWNLOAD_PATH = "/home/ichheit/Downloads/MusicPlayer";


/**
 * @brief  搜索条数
 */
static const int MUSIC_DOWNLOAD_LIMIT = 60;

/**
 * @brief  网易云歌曲信息结构（可用于存储从网易云搜索到的数据）
 */
typedef struct _SONG_INFO{
    int nID;
    QString strArtists;
    QString strSong;
    QString strAlbum;
    int nTime; // 毫秒时间
    /**
     * @brief  用于显示歌曲列表时附加信息（下载百分比状态）
     *  -1 用于表示从未下载
     *  -2 表示网络文件无效
     *  -3 表示网络连接错误
     *  -4 表示本地存储失败
     */
    int nPercentage;
} SONGINFO;

/**
 * @brief  歌曲搜索结果结构
 */
struct SongSearchResult
{
    bool bCurrentSearchDone;       //标记本次搜索是否结束
    bool bAppendToList;            //是否为追加到列表，false 则先清空
    QVector<SONGINFO> vecSongInfo; //获取的所有歌曲信息
    bool bShowUnexpectedResultTip; //是否显示意外结果的提示
    QString strUnexpectedResultTip;//意外结果的提示
};

//储存获取的单个歌词信息
struct LyricInfo
{
    QString strPlaneText;
    QString strLabelText;
    QString strSong;
    QString strArtist;
    QString strLyricFrom;
};

#endif // SONGSEARCHRESULT_H
