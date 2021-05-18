INCLUDEPATH +=$$PWD MP3Editor
include(MP3Editor/mp3Editor.pri)

HEADERS+= \
    $$PWD/NetAccess.h \
    $$PWD/SearcherNetEaseCloud.h \
    $$PWD/SongSearchResult.h \
    $$PWD/ThreadConvertMp3.h \
    $$PWD/ThreadSearchNcmMusic.h \
    $$PWD/LrcProcessor.h \
    $$PWD/UnicodeReader.h

SOURCES+= \
    $$PWD/NetAccess.cpp \
    $$PWD/SearcherNetEaseCloud.cpp \
    $$PWD/ThreadConvertMp3.cpp \
    $$PWD/LrcProcessor.cpp
