set(BINARY Algorithm)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

add_library(${BINARY}_lib STATIC ${SOURCES})
