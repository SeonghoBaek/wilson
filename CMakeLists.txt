cmake_minimum_required(VERSION 3.2)
project(nodebus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(INCLUDE_DIRECTORIES "bus/include:/usr/include/libxml2")
include_directories(bus/include)
include_directories(/usr/include/libxml2)

set(SOURCE_FILES
    bus/src/BigNode.cpp
    bus/src/Bridge.cpp
    bus/src/ClientNode.cpp
    bus/src/DefaultGlobalService.cpp
    bus/src/DefaultService.cpp
    bus/src/GlobalBusInit.cpp
    bus/src/INodeBusService.cpp
    #bus/src/LocalBusInit.cpp
    bus/src/Lock.cpp
    bus/src/Log.cpp
    bus/src/NodeLooper.cpp
    bus/src/NodeNetwork.cpp
    bus/src/NodePort.cpp
    bus/src/Normalizer.cpp
    bus/src/Packet.cpp
    bus/src/Queue.cpp
    bus/src/XMLParser.cpp
    #node/atm/src/atm.cpp
    #node/pionode/src/AtmgrInterface.cpp
    #node/pionode/src/AtmgrInterface.h
    #node/pionode/src/Pionode.cpp
    #node/pionode/src/Pionode.h
    #node/pionode/src/sqlite3.h
    #node/plogman/src/plogman
    )

set(HEADER_FILES
    bus/include/BigNode.h
    bus/include/Bridge.h
    bus/include/ClientNode.h
    bus/include/Configure.h
    bus/include/DefaultGlobalService.h
    bus/include/DefaultService.h
    bus/include/IMessageService.h
    bus/include/INameService.h
    bus/include/INodeBusService.h
    bus/include/List.h
    bus/include/Lock.h
    bus/include/Log.h
    bus/include/NodeBus.h
    bus/include/NodeBusService.h
    bus/include/NodeEntry.h
    bus/include/NodeLooper.h
    bus/include/NodeNetwork.h
    bus/include/NodePort.h
    bus/include/Normalizer.h
    bus/include/Packet.h
    bus/include/Thread.h
    bus/include/Types.h
    bus/include/XMLParser.h
    bus/include/XMLTypes.h
    )

add_executable(nodebus ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(nodebus xml2)