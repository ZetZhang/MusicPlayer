#include "LrcProcessor.h"
#include "UnicodeReader.h"

#include <QRegExp>
#include <QFile>

bool LrcProcessor::LoadFromFile(QString lyricFilePath)
{
    lrcLyrics.clear();

    //先读取所有文本
    QVector<QString> lines;

    bIsLyricValid = false;
    bIsLrcLyric = false;
    bIsNeteaseLrcFormat = true;

    QString content;
    UnicodeReader unicodeReader;
    if(!unicodeReader.ReadFromFile(lyricFilePath, content))
        return false;

    QRegExp sepRegExp = QRegExp("\n|\r");               //linux\mac\windows 换行符号
    QStringList lineList = content.split(sepRegExp);

    for(auto& line: lineList)
    {
        line = line.trimmed();
        if(!line.isEmpty())
            lines.push_back(line.trimmed());
    }

    LoadFromRawLines(lines);

    return true;
}

bool LrcProcessor::LoadFromRawText(QString content)
{
    QStringList lineList = content.split('\n');
    QVector<QString> lines;
    for(auto line:lineList)
    {
        line = line.trimmed();
        if(!line.isEmpty())
            lines.push_back(line);
    }

    LoadFromRawLines(lines);

    return true;
}

void LrcProcessor::LoadFromRawLines(QVector<QString> lines)
{
    //进一步判断是否为LRC歌词
    if(lines.size() != 0) {
        bIsLyricValid = true;
        QVector<QPair<int, QString>> lrcLyricsTemp; //临时存放初步收集的可能无序的结果

        //这里判断的标准以 比较广泛的方式支持读取进来
        //网易云标准上传的歌词格式只有 带时间标签的行，而且一行一个时间 [xx:xx.xx]  xxx
        //广泛的lrc格式，可能包含 [ar:歌手名]、[ti:歌曲名]、[al:专辑名]、[by:编辑者(指lrc歌词的制作人)]、[offset:时间补偿值]
        //时间标签，形式为“[mm:ss]”或“[mm:ss.ff]” 一行可能包含多个时间标签

        QStringList infoLabels;     //储存非歌词行的信息 [ar:歌手名] 、[offset:时间补偿值] 等

        QRegExp rx_time("(\\[\\s*\\d+\\s*:\\s*\\d+(\\.\\d+)?\\s*\\])");  //匹配时间标签
        QRegExp rx_other("(\\[\\s*\\w+\\s*:\\s*\\w+\\s*\\])");  //匹配其他标签
        for(auto& line : lines) {
            QStringList timeList;
            //非标签文本开始的位置
            int textPos = 0;
            //尝试匹配时间标签
            int pos = 0;
            while ((pos = rx_time.indexIn(line, pos)) != -1) {
                timeList << rx_time.cap(1);
                pos += rx_time.matchedLength();
                textPos = pos;
            }
            //尝试匹配其他标签
            int pos2 = 0;
            while ((pos2 = rx_other.indexIn(line, pos2)) != -1) {
                infoLabels << rx_other.cap(1);
                pos2 += rx_other.matchedLength();
                textPos = pos2;
            }
            QString strLeft; //剩下的字符串
            strLeft = line.right(line.size()-textPos);   //得到去除可能的标签后的字符串

            for(auto& time: timeList) { //只有当收集到时间标签时，才收集对应的歌词进入 lrcLyricsTemp
                //将时间标签转化为 毫秒时间
                int p1 = time.indexOf('[');

                time = time.right(time.size()-p1-1);
                int p2 = time.indexOf(':');

                QString strMin = time.left(p2);

                time = time.right(time.size()-p2-1);
                int p3 = time.indexOf(']');

                QString strSec = time.left(p3);
                int min = strMin.toInt();
                double sec = strSec.toDouble();
                int msec = min * 60 * 1000 + int(sec * 1000);
                lrcLyricsTemp.push_back(QPair<int,QString>(msec,strLeft));
            }
            if(timeList.size() > 1)  //一行包含多个时间，认为不是标准的网易云音乐歌词
                bIsNeteaseLrcFormat = false;
        }

        if (lrcLyricsTemp.size() != 0) {
            //认为是lrc歌词
            bIsLrcLyric = true;
            //对收集到的 lrcLyricsTemp 根据时间，从小到大排序，置于  lrcLyrics 中
            while(lrcLyricsTemp.size()!=0) {
                int minTime = lrcLyricsTemp.front().first;
                auto iterDel = lrcLyricsTemp.begin();           //存放最小的要被删除的那个
                for(auto iter = lrcLyricsTemp.begin()+1; iter != lrcLyricsTemp.end(); iter++) {
                    if(iter->first < minTime) {
                        iterDel = iter;
                        minTime = iter->first;
                    }
                }
                lrcLyrics.push_back(*iterDel);
                lrcLyricsTemp.erase(iterDel);
            }
            if(infoLabels.size() != 0)//包含时间标签外的其他类型标签，认为不是标准的网易云音乐歌词
                bIsNeteaseLrcFormat = false;

            GatherInfoMap(infoLabels);
            //查看 infoLabels中是否存在  [offset:时间补偿值]，存在则修正时间
            if(offsetVaule != 0) {
                for(auto& lrc: lrcLyrics) {
                    lrc.first += offsetVaule;
                    if(lrc.first < 0)
                        lrc.first = 0;
                }
            }
        } else {
            //找不到任何含有时间标签的行，认为是原生歌词
            bIsLrcLyric = false;
            //收集歌词到 lrcLyric 结构中，时间都置为 0
            for(auto& line:lines)
                lrcLyrics.push_back(QPair<int,QString>(0,line));
        }
    }

}

QVector<QPair<int, QString>> LrcProcessor::GetLrcLyric()
{
    return lrcLyrics;
}

QString LrcProcessor::ToLrcLine(QPair<int, QString> timeLine)
{
    int pos = timeLine.first;
    int ms = pos % 1000;
    pos = pos / 1000;
    int s = pos % 60;
    int m = pos / 60;

    QString timeLabel;
    timeLabel.sprintf("[%.2d:%.2d.%.3d]", m, s, ms);

    return timeLabel + timeLine.second;
}


void LrcProcessor::GatherInfoMap(QStringList infoLabels)
{
     QMap<QString,QString> infoMap;

    //查看 infoLabels中是否存在  [offset:时间补偿值]，存在则修正时间
    for(auto label:infoLabels)
    {
       int pos1 = label.indexOf('[');
       int pos2 = label.indexOf(':');
       int pos3 = label.indexOf(']');
       if(pos1 == -1|| pos2 == -1 || pos3 == -1 )
           continue;  //无效标签，继续

       QString key = label.left(pos2).right(pos2-pos1-1);
       QString value = label.right(pos3 - pos2);
       pos3 = value.indexOf(']');
       value = value.left(pos3);

       infoMap.insert(key,value);
    }

    m_strTitle = infoMap["ti"];
    m_strArtist = infoMap["ar"];
    m_strAlbum = infoMap["al"];
    m_strEditor = infoMap["by"];
    offsetVaule = infoMap["offset"].toInt();
}
