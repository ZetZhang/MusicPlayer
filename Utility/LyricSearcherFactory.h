#pragma once
#ifndef LYRICSEARCHFACTORY_H
#define LYRICSEARCHFACTORY_H

#include "ISearch.h"
#include "SearcherNetEaseCloud.h"
#include <QSharedPointer>
#include <assert.h>

class CLyricSearcherFactory
{
public:
    static QSharedPointer<ISearcher> CreateSearcher(SEARCH_FROM search_from)
	{
        switch(search_from)
        {
//        case SF_GECIMI:
//           return QSharedPointer<ISearcher>(new SearcherGecimi());
        case SF_NETEASE:
           return QSharedPointer<ISearcher>(new SearcherNetEaseCloud());
        default:
            assert(false && "未知的歌词搜索类型");
            break;
        }
        return QSharedPointer<ISearcher>(nullptr);
	}

};

#endif // LYRICSEARCHFACTORY_H
