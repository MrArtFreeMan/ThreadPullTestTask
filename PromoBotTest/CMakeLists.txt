# CMakeList.txt : CMake project for PromoBotTest

SET(MYCOMPILE_FLAGS "-pthread")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MYCOMPILE_FLAGS}")

add_executable (PromoBotTest "PromoBotTest.cpp" "PromoBotTest.h" "ThreadPull/ThreadPull.cpp" "ThreadPull/ThreadPull.h" "App/App.cpp" "App/App.h" "ThreadPull/DataStructs.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PromoBotTest PROPERTY CXX_STANDARD 20)
endif()

