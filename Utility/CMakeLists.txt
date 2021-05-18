set(UtilityFiles
    ./NetAccess.cpp
    ./ThreadConvertMp3.cpp
    ./SearcherNetEaseCloud.cpp
    )

add_library(Utility ${UtilityFiles})

file(GLOB HEADERS "*.h")

install(TARGETS Utility DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

add_subdirectory(MP3Editor)
