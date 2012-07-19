file(GLOB SRCS *.c)
file(GLOB HDRS *.h)

add_library(corc.core SHARED ${SRCS} ${HDRS})
