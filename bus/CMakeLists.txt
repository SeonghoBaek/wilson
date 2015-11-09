cmake_minimum_required(VERSION 2.8)
project(wilson)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/usr/local/bin/wilson")

include_directories(include)
include_directories(/usr/include/libxml2)

set(SOURCE_FILES
    src/BigNode.cpp
    src/Bridge.cpp
    src/ClientNode.cpp
    src/DefaultGlobalService.cpp
    src/DefaultService.cpp
    src/GlobalBusInit.cpp
    src/INodeBusService.cpp
    #src/LocalBusInit.cpp
    src/Lock.cpp
    src/Log.cpp
    src/NodeLooper.cpp
    src/NodeNetwork.cpp
    src/NodePort.cpp
    src/Normalizer.cpp
    src/Packet.cpp
    src/Queue.cpp
    src/XMLParser.cpp
    #node/atm/src/atm.cpp
    #node/pionode/src/AtmgrInterface.cpp
    #node/pionode/src/AtmgrInterface.h
    #node/pionode/src/Pionode.cpp
    #node/pionode/src/Pionode.h
    #node/pionode/src/sqlite3.h
    #node/plogman/src/plogman
    )

set(CLIENT_SOURCE_FILES
        src/BigNode.cpp
        src/Bridge.cpp
        src/ClientNode.cpp
        src/DefaultGlobalService.cpp
        src/DefaultService.cpp
        #src/GlobalBusInit.cpp
        src/INodeBusService.cpp
        src/LocalBusInit.cpp
        src/Lock.cpp
        src/Log.cpp
        src/NodeLooper.cpp
        src/NodeNetwork.cpp
        src/NodePort.cpp
        src/Normalizer.cpp
        src/Packet.cpp
        src/Queue.cpp
        src/XMLParser.cpp
#node/atm/src/atm.cpp
#node/pionode/src/AtmgrInterface.cpp
#node/pionode/src/AtmgrInterface.h
#node/pionode/src/Pionode.cpp
#node/pionode/src/Pionode.h
#node/pionode/src/sqlite3.h
#node/plogman/src/plogman
)

set(HEADER_FILES
    include/BigNode.h
    include/Bridge.h
    include/ClientNode.h
    include/Configure.h
    include/DefaultGlobalService.h
    include/DefaultService.h
    include/IMessageService.h
    include/INameService.h
    include/INodeBusService.h
    include/List.h
    include/Lock.h
    include/Log.h
    include/NodeBus.h
    include/NodeBusService.h
    include/NodeEntry.h
    include/NodeLooper.h
    include/NodeNetwork.h
    include/NodePort.h
    include/Normalizer.h
    include/Packet.h
    include/Thread.h
    include/Types.h
    include/XMLParser.h
    include/XMLTypes.h
    )

add_executable(wilson ${SOURCE_FILES} ${HEADER_FILES})

add_executable(wilson_client ${CLIENT_SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(wilson xml2)
target_link_libraries(wilson_client xml2)
