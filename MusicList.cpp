#include "MusicList.h"
#include "MusicListWidget.h"

#include <QCoreApplication>
#include <QProgressDialog>
#include <QDesktopServices>
#include <QtSql>
#include <algorithm>
#include <QMessageBox>

/**
 * @brief  MusicList 构造
 *
 * @param  urls
 * @param  iname
 */
MusicList::MusicList(const QList<QUrl> &urls, QString iname)
{
    addMusic(urls);
    setName(iname);
}

/**
 * @brief  addMusic 从url添加歌曲
 *
 * @param  urls
 */
void MusicList::addMusic(const QList<QUrl> &urls)
{
    // 实测这里耗时较长，所以添加一个进度显示对话框
    QProgressDialog proDialog(u8"添加进度", u8"取消", 0, urls.size());
    proDialog.setMinimumSize(350,150);
    proDialog.setWindowModality(Qt::WindowModal);
    proDialog.setWindowTitle("添加中...请稍后");
    proDialog.show();
    int x = 0;
    foreach (QUrl i, urls) {
        x++;
        proDialog.setValue(x);
        // 过滤Url的类型
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForFile(i.toLocalFile());
        if(mime.name() != "audio/mpeg" && mime.name() != "audio/flac"){
            continue;
        }
        // 剩下的符合类型
        music.push_back(Music(i));
        if(sql_flag){
            music[music.size()-1].insertSQL(name);
        }
        if(proDialog.wasCanceled()) break;
    }
}

/**
 * @brief  addMusic 添加一首歌曲
 *
 * @param  iMusic
 */
void MusicList::addMusic(const Music &iMusic)
{
    music.push_back(iMusic);
    if(sql_flag){
        music[music.size()-1].insertSQL(name);
    }
}

/**
 * @brief  getMusic 获取指定位置歌曲
 *
 * @param  pos
 *
 * @return   
 */
Music MusicList::getMusic(int pos)
{
    return music[pos];
}

/**
 * @brief  addToPlayList 将本歌单加入播放列表
 *
 * @param  playlist
 */
void MusicList::addToPlayList(QMediaPlaylist *playlist)
{
    for(auto i = music.begin(); i != music.end(); i++){
        playlist->addMedia(i->getUrl());
    }
}

/**
 * @brief  addToListWidget 歌单可视化
 *
 * @param  listWidget
 */
void MusicList::addToListWidget(MusicListWidget *listWidget)
{
    foreach(const Music &i,music){
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(listWidget->getIcon());
        item->setText(i.getInfo());
        listWidget->addItem(item);
    }
}

/**
 * @brief  removeMusic 移除指定的歌曲
 *
 * @param  pos
 */
void MusicList::removeMusic(int pos)
{
    if (sql_flag) {
        remove_SQL_all();
        int i = 0;
        for (auto it = music.begin(); it != music.end(); ) {
            if(i == pos) {
                it = music.erase(it);
                break;
            } else {
                it++;
            }
            i++;
        }
        insert_SQL_all();    
    } else {
        int i = 0;
        for (auto it = music.begin(); it != music.end(); ) {
            if (i == pos) {
                it = music.erase(it);
                break;
            } else {
                it++;
            }
            i++;
        }
    }
}

/**
 * @brief  showInExplorer 在文件夹中打开
 *
 * @param  pos
 */
void MusicList::showInExplorer(int pos)
{
    QString str=music[pos].getUrl().toString();
    str.remove(str.split("/").last());//切割字符串获得所在的文件夹路径
    QDesktopServices::openUrl(str);
}

/**
 * @brief  detail 显示制定歌曲详细信息
 *
 * @param  pos
 */
void MusicList::detail(int pos)
{
    music[pos].detail();
}

/**
 * @brief  remove_SQL_all 数据库中移除全部本歌单的歌曲
 */
void MusicList::remove_SQL_all()
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from MusicInfo where name = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(name);
    sql_query.exec();
}

/**
 * @brief  insert_SQL_all 将歌单中歌曲全部写入数据库
 */
void MusicList::insert_SQL_all()
{
    for(auto i=music.begin();i!=music.end();i++){
        i->insertSQL(name);
    }
}

/**
 * @brief  read_fromSQL 从数据中恢复本歌单
 */
void MusicList::read_fromSQL()
{
    QSqlQuery sql_query;
    QString select_sql = "select url, author, title, duration, albumTitle, audioBitRate from MusicInfo where name = ?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(name);

    if (sql_query.exec()) {
        while(sql_query.next()) {
            Music tempMusic;
            tempMusic.url = QUrl(sql_query.value(0).toString());
            tempMusic.author = sql_query.value(1).toString();
            tempMusic.title = sql_query.value(2).toString();
            tempMusic.duration = sql_query.value(3).toLongLong();
            tempMusic.albumTitle = sql_query.value(4).toString();
            tempMusic.audioBitRate = sql_query.value(5).toInt();
            music.push_back(tempMusic);
        }  
    }
}

/**
 * @brief  sort_by 排序
 *
 * @param  key
 */
void MusicList::sort_by(COMPARE key)
{
    sort(music.begin(),music.end(),MusicCompare(key));
    if(sql_flag){
        remove_SQL_all();
        insert_SQL_all();
    }
}

/**
 * @brief  neaten 去重排序
 */
void MusicList::neaten()
{
    sort(music.begin(),music.end(),MusicCompare(DEFAULT));
    music.erase(unique(music.begin(),music.end(),MusicCompare(EQUALITY)), music.end());
    if(sql_flag){
        remove_SQL_all();
        insert_SQL_all();
    }
}

/**
 * @brief  clear 清空歌单
 */
void MusicList::clear()
{
    music.clear();
    if(sql_flag){
        remove_SQL_all();    
    }
}
