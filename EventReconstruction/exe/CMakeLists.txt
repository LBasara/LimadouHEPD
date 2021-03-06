# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
#project(exe)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

if(WIN32)	
 find_package( ROOT REQUIRED COMPONENTS libCore libRIO libNet libTree libHist )
elseif(UNIX)
 find_package( ROOT REQUIRED COMPONENTS RIO Net Tree Hist )
endif()

include(${ROOT_USE_FILE})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/Common/include
		    ${CMAKE_SOURCE_DIR}/Tracker/include
                    ${CMAKE_SOURCE_DIR}/Calo/include)

#file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/*/src/*.cc)

add_executable(CalibrateTracker CalibrateTracker.cc ${sources})
add_executable(CalibrateCalo CalibrateCalo.cc ${sources})
add_executable(Calibrate Calibrate.cc ${sources})
add_executable(Reco01 Reco01.cc ${sources})
add_executable(L1Reader L1Reader.cc ${sources})


target_link_libraries(CalibrateTracker ${ROOT_LIBRARIES})
target_link_libraries(CalibrateCalo ${ROOT_LIBRARIES})
target_link_libraries(Calibrate ${ROOT_LIBRARIES})
target_link_libraries(Reco01 ${ROOT_LIBRARIES})
target_link_libraries(L1Reader ${ROOT_LIBRARIES})









get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()



