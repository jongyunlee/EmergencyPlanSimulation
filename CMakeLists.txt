PROJECT(Project)

cmake_minimum_required(VERSION 2.8)

# collect source files
FILE( GLOB_RECURSE SRC src/*.cpp core/*.cpp )
FILE( GLOB_RECURSE HDR src/*.h src/*.frag src/*.vert src/*.geom core/**/*.h core/**/*.frag core/**/*.vert core/**/*.geom )

# depends on OS
IF (UNIX)

   ADD_EXECUTABLE( project ${SRC} ${HDR} )
   FIND_PACKAGE(OpenGL REQUIRED)
   FIND_PACKAGE(GLUT REQUIRED)
   FIND_PACKAGE(GLEW REQUIRED)
   INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
   TARGET_LINK_LIBRARIES( project ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})

ELSE (UNIX)
   # Common include / link directories
   INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/freeglut/include/ ${CMAKE_SOURCE_DIR}/glew/inc/ )
   LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/freeglut/lib/ ${CMAKE_SOURCE_DIR}/glew/lib/)

   SET( EXTERNAL_LINK_LIBS freeglut.lib glew32.lib )

   ADD_EXECUTABLE( project ${SRC} ${HDR} )
   TARGET_LINK_LIBRARIES( project ${EXTERNAL_LINK_LIBS} )

   # copy DLLS
   FILE(GLOB_RECURSE DLLS ${CMAKE_SOURCE_DIR}/freeglut/*.dll ${CMAKE_SOURCE_DIR}/glew/*.dll)
   SOURCE_GROUP("DLL Files" FILES ${DLLS})
   FILE(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR})

ENDIF (UNIX)
