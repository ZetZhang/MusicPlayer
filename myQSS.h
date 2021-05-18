#ifndef MYQSS_H
#define MYQSS_H

#include<QString>

/* 此文件统一存放一些QSS样式代码 */

/**
 * @brief  PlayStyle 播放按钮样式
 *
 * @return   
 */
inline QString PlayStyle()
{
    return
"           QPushButton {"
"               background-image:url(:/image/image/image/play.png);"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               border:none;"
"           }"
    
"           QPushButton:hover{"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image-hover/play-hover.png);"
"           }"

"           QPushButton:pressed{"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image/play.png);"
"           }";
}

/**
 * @brief  PaseStyle 暂停按钮样式
 *
 * @return   
 */
inline QString PaseStyle()
{
    return
"           QPushButton {"
"               background-image:url(:/image/image/image/pase.png);"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               border:none;"
"           }"

"           QPushButton:hover {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image-hover/pase-hover.png);"
"           }"

"           QPushButton:pressed {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image/pase.png);"
"           }";
}

/**
 * @brief  RandomStyle 随机
 *
 * @return   
 */
inline QString RandomStyle()
{
    
    return
"           QPushButton {"
"               background-image:url(:/image/image/image/play-random.png);"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               border:none;"
"           }"

"           QPushButton:hover {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image-hover/play-random-hover.png);"
"           }"

"           QPushButton:pressed {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image/play-random.png);"
"           }";
}

/**
 * @brief  LoopStyle 循环
 *
 * @return   
 */
inline QString LoopStyle()
{


    return
"           QPushButton {"
"               background-image:url(:/image/image/image/loop.png);"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               border:none;"
"           }"

"           QPushButton:hover {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image-hover/loop-hover.png);"
"           }"

"           QPushButton:pressed {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image/loop.png);"
"           }";
}

/**
 * @brief  LoopOneStyle 单曲循环
 *
 * @return   
 */
inline QString LoopOneStyle()
{


    return
"           QPushButton {"
"               background-image:url(:/image/image/image/loop-one.png);"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               border:none;"
"           }"

"           QPushButton:hover {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image-hover/loop-one-hover.png);"
"           }"

"           QPushButton:pressed {"
"               background-repeat:no-repeat;"
"               background-position:center center;"
"               background-image:url(:/image/image/image/loop-one.png);"
"           }";
}

/**
 * @brief  ListWidgetStyle 
 *
 * @return   
 */
//inline QString ListWidgetStyle(){
//    return
//"           QScrollBar:vertical {"
//"               width:8px;"
//"               background-color:transparent;"
//"               margin:0px,0px,0px,0px;"
//"               padding-top:12px;   /*上预留位置*/"
//"               padding-bottom:12px;    /*下预留位置*/"
//"           }"
 
//"           QScrollBar::handle:vertical {"
//"               width:8px;"
//"               background-color:rgba(255,255,255,0.2);"
//"               border-radius:4px;"
//"               min-height:20px;"
//"           }"
 
 
//"           QScrollBar::handle:vertical:hover {"
//"               width:9px;"
//"               background-color:rgba(255,255,255,0.5);"
//"               border-radius:4px;"
//"               min-height:20;"
//"           }"
 
//"           QScrollBar::add-line:vertical {"
//"               height:12px;"
//"               width:10px;"
//"               border-image:url(:/selectfile/scroll/3.png);"
//"               subcontrol-position:bottom;"
//"           }"

//"           QScrollBar::sub-line:vertical {"
//"               height:12px;"
//"               width:10px;"
//"               border-image:url(:/selectfile/scroll/1.png);"
//"               subcontrol-position:top;"
//"           }"

//"           QScrollBar::add-line:vertical:hover {"
//"               height:12px;"
//"               width:10px;"
//"               border-image:url(:/selectfile/scroll/4.png);"
//"               subcontrol-position:bottom;"
//"           }"

//"           QScrollBar::sub-line:vertical:hover"
//"           {"
//"               height:12px;"
//"               width:10px;"
//"               border-image:url(:/selectfile/scroll/2.png);"
//"               subcontrol-position:top;"
//"           }"
 
//"           QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical {"
//"               background-color:transparent;"
//"               border-radius:4px;"
//"           }";
//}

/**
 * @brief  m_pBtnPreviewSongStyle 查看歌曲列表按钮
 *
 * @return   
 */
inline QString m_pBtnPreviewSongStyle()
{
    return
"           QPushButton#m_pBtnPreviewSong {"
"               border: none; "
"               background-color: rgba(0, 0, 0, 50); "
"               image:url(:/image/image/image/view_music_normal_white.png);"
"           }"

"           QPushButton#m_pBtnPreviewSong:hover{"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/view_music_hover_white.png);"
"           } "

"           QPushButton#m_pBtnPreviewSong:pressed {"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/view_music_hover_white.png);"
"           }";
}

/**
 * @brief  m_pBtnListenSongStyle 试听歌曲列表按钮
 *
 * @return   
 */
inline QString m_pBtnListenSongStyle()
{
    return
"           QPushButton#m_pBtnListenSong{"
"               border: none; "
"               background-color: rgba(0, 0, 0, 50); "
"               image:url(:/image/image/image/listen_music_normal_white.png);"
"           }"

"           QPushButton#m_pBtnListenSong:hover{"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/listen_music_hover_white.png);"
"           } "

"           QPushButton#m_pBtnListenSong:pressed {"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/listen_music_hover_white.png);"
"           }";
}

/**
 * @brief  m_pBtnDownloadSongStyle 下载歌曲列表按钮
 *
 * @return   
 */
inline QString m_pBtnDownloadSongStyle()
{
    return
"           QPushButton#m_pBtnDownloadSong{"
"               border: none; "
"               background-color: rgba(0, 0, 0, 50); "
"               image:url(:/image/image/image/download_music_item_normal_white.png);"
"           }"

"           QPushButton#m_pBtnDownloadSong:hover{"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/download_music_item_hover_white.png);"
"           } "

"           QPushButton#m_pBtnDownloadSong:pressed {"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/download_music_item_hover_white.png);"
"           }";
}

/**
 * @brief  m_pBtnDownloadSongStyle 下载歌词列表按钮
 *
 * @return
 */
inline QString m_pBtnDownloadLyricStyle()
{
    return
"           QPushButton#m_pBtnDownloadLyric{"
"               border: none; "
"               background-color: rgba(0, 0, 0, 50); "
"               image:url(:/image/image/image/download_lyric_item_normal_white.png);"
"           }"

"           QPushButton#m_pBtnDownloadLyric:hover{"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/download_lyric_item_hover_white.png);"
"           } "

"           QPushButton#m_pBtnDownloadLyric:pressed {"
"               background-color: rgba(255, 255, 255, 70); "
"               image:url(:/image/image/image-hover/download_lyric_item_hover_white.png);"
"           }";
}

/**
 * @brief  tableViewMenuStyle 右键菜单选项样式
 *
 * @return
 */
inline QString tableViewMenuStyle()
{
    return
"           QMenu {"
"               color:rgb(0, 0, 0);"
"               background-color:rgba(255, 255, 255, 90);"
"               width:90px;"
"               border:none;"
"           }"

"           QMenu::separator {"
"               height:1px;"
"               background-color:rgba(0,0,0,1);"
"           }"

"           QMenu::item: {"
"               color:rgb(123,123,123);"
"               background-color:#fecb3f;"
"           }";
}

#endif // MYQSS_H
