set(CloudMusicFiles
    ./BesTableView.cpp
    ./BesTableModel.cpp
    ./BesButtonDelegate.cpp
    )

add_library(CloudMusic ${CloudMusicFiles})

file(GLOB HEADERS "*.h")

install(TARGETS CloudMusic DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
