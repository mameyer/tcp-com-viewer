project(tcpcomviewer)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

SET(tcpserverviewer_SOURCES server/TcpServerViewer.cpp server/main.cpp ../tcp-communication/server/TCPServer.cpp ../tcp-communication/common/common.cpp ../tcp-communication/common/Subject.cpp)
SET(tcpserverviewer_HEADERS server/TcpServerViewer.hpp)

SET(tcpclientviewer_SOURCES client/TcpClientViewer.cpp client/main.cpp ../tcp-communication/client/TCPClient.cpp ../tcp-communication/common/Subject.cpp)
SET(tcpclientviewer_HEADERS client/TcpClientViewer.hpp)

qt4_wrap_cpp(tcpserverviewer_MOC ${tcpserverviewer_HEADERS})
qt4_wrap_ui(tcpserverviewer_UI server/tcpServerViewer.ui)

qt4_wrap_cpp(tcpclientviewer_MOC ${tcpclientviewer_HEADERS})
qt4_wrap_ui(tcpclientviewer_UI client/tcpClientViewer.ui)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(tcpserverviewer ${tcpserverviewer_SOURCES} 
    ${tcpserverviewer_MOC}
    ${tcpserverviewer_UI})
TARGET_LINK_LIBRARIES(tcpserverviewer ${QT_LIBRARIES} pthread)

ADD_EXECUTABLE(tcpclientviewer ${tcpclientviewer_SOURCES} 
    ${tcpclientviewer_MOC}
    ${tcpclientviewer_UI})
TARGET_LINK_LIBRARIES(tcpclientviewer ${QT_LIBRARIES} pthread)