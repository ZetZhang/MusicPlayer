set(mp3EditorFiles
    ./mp3Editor.cpp
    )

add_library(mp3Editor ${mp3EditorFiles})

file(GLOB HEADERS "*.h")

install(TARGETS mp3Editor DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
