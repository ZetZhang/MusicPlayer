#pragma once

#include <QMap>
#include <QPair>
#include <QVector>
#include <QString>

class LrcProcessor
{
public:
    bool LoadFromFile(QString filePath);

    bool LoadFromRawText(QString content);

    void LoadFromRawLines(QVector<QString> lines);

    QVector<QPair<int, QString>> GetLrcLyric();

    static QString ToLrcLine(QPair<int, QString> timeLine);

private:
    void GatherInfoMap(QStringList infoLabels);

public:
    QString	m_strTitle;					/* 歌曲标题 */
    QString	m_strArtist;				/* 艺术家 */
    QString	m_strAlbum;					/* 专辑 */
    QString	m_strEditor;				/* 编辑的人 */
    int offsetVaule;
    QVector<QPair<int, QString>> lrcLyrics;

public:
    bool bIsLyricValid;
    bool bIsLrcLyric;
    bool bIsNeteaseLrcFormat;
};

