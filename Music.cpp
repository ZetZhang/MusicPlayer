#include "Music.h"

#include <QtSql>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QCoreApplication>

/**
 * @brief  Music 初始化
 *
 * @param  iurl
 */
Music::Music(QUrl iurl)
{
    url = iurl;
    refreshInfo();
}

/**
 * @brief  formatTime 引用外部formatTime函数
 *
 * @param  timeMilliSeconds
 *
 * @return   
 */
extern QString formatTime(qint64 timeMilliSeconds);

/**
 * @brief  refreshInfo 根据歌曲url获得歌曲信息
 */
void Music::refreshInfo()
{
    QMediaPlayer tempPlayer;
    tempPlayer.setMedia(url);
    // 元数据的解析需要时间，所以这里需要循环等待（但同时需要保持Qt事件处理机制在运行）
    while (!tempPlayer.isMetaDataAvailable()) {
        QCoreApplication::processEvents();
    }
    // 调试时查看有哪些元数据可用
    // AlbumTitle, ContributingArtist, CoverArtImage, Title, container-format, encoder
    // QStringList list = tempPlayer.availableMetaData();
    // QMessageBox::about(Q_NULLPTR, "0000", list.join(","));
    if(tempPlayer.isMetaDataAvailable()){
        //歌曲信息
        author       = tempPlayer.metaData(QMediaMetaData::ContributingArtist).toStringList().join(","); // 不是Author?
        title        = tempPlayer.metaData(QMediaMetaData::Title).toString();
        albumTitle   = tempPlayer.metaData(QMediaMetaData::AlbumTitle).toString();
        audioBitRate = tempPlayer.metaData(QMediaMetaData::AudioBitRate).toInt(); // 可能无效
        duration     = tempPlayer.duration();
    }
}

/**
 * @brief  getLyricFile 根据文件名获取歌词路径
 *
 * @return   
 */
QString Music::getLyricFile()
{
    QString mp3FilePath=url.toLocalFile();
    mp3FilePath.replace(".mp3", ".lrc");
    mp3FilePath.replace(".flac", ".lrc");
    mp3FilePath.replace(".mpga", ".lrc");
    return mp3FilePath;
}

/**
 * @brief  getInfo 返回歌曲信息
 *
 * @return   
 */
QString Music::getInfo() const
{
    return author + " - " + title + " [" + formatTime(duration) + "]";
}

/**
 * @brief  detail 歌曲详细
 */
void Music::detail()
{
    QString info("歌曲名：%1\n艺术家：%2\n时长：%3\n唱片集：%4\n比特率：%5\n文件路径：%6");
    info = info.arg(title, author, formatTime(duration), albumTitle, QString::number(audioBitRate)+"bps", url.toString());
    QMessageBox::about(Q_NULLPTR, "歌曲信息", info);
}

/**
 * @brief  insertSQL 保存到数据库
 *
 * @param  name
 */
void Music::insertSQL(const QString &name)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into MusicInfo values (?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(name);
    sql_query.addBindValue(url.toString());
    sql_query.addBindValue(author);
    sql_query.addBindValue(title);
    sql_query.addBindValue(duration);
    sql_query.addBindValue(albumTitle);
    sql_query.addBindValue(audioBitRate);
    sql_query.exec();
}

/**
 * @brief  operator() ()操作符重载，用于排序比较
 *
 * @param  A
 * @param  B
 *
 * @return   
 */
bool MusicCompare::operator()(const Music &A, const Music &B)
{
    switch (key) {
        case TITLE:
            return A.title<B.title;
        case AUTHOR:
            return A.author<B.author;
        case DURATION:
            return A.duration<B.duration;
        case EQUALITY:
            return A.getUrl()==B.getUrl();
        default:
            return A.getInfo()<B.getInfo();
    }
}
