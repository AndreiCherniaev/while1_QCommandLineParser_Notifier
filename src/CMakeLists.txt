cmake_minimum_required(VERSION 3.16)

project(while1_QCommandLineParser_Notifier LANGUAGES CXX) #use for ${PROJECT_NAME}

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(${PROJECT_NAME}
  Worker.cpp Worker.h
  MainClass.cpp MainClass.h
  main.cpp
  qconsolelistener.h qconsolelistener.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Core)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
