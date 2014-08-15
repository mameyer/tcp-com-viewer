project(tcpcomviewer)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

SET(tcpcomviewer_SOURCES src/TcpComViewer.cpp src/main.cpp ../tcp-communication/server/TCPServer.cpp ../tcp-communication/common/common.cpp)
SET(tcpcomviewer_HEADERS src/TcpComViewer.hpp)

qt4_wrap_cpp(tcpcomviewer_MOC ${tcpcomviewer_HEADERS})
qt4_wrap_ui(tcpcomviewer_UI src/tcpComViewer.ui)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(tcpcomviewer ${tcpcomviewer_SOURCES} 
    ${tcpcomviewer_MOC}
    ${tcpcomviewer_UI})
TARGET_LINK_LIBRARIES(tcpcomviewer ${QT_LIBRARIES} pthread)