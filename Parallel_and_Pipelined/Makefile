APPSOURCES = image.cpp main.cpp haar.cpp 
EXECUTABLE = face.elf

PLATFORM = zc706
SDSFLAGS = -sds-pf ${PLATFORM} \
	-sds-hw detectFaces haar.cpp -clkid 3 -sds-end \
	-poll-mode 1  
	

CC = sds++ ${SDSFLAGS}

CFLAGS = -Wall -O3 -c
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
LFLAGS = -O3

OBJECTS := $(APPSOURCES:.cpp=.o)
DEPS := $(OBJECTS:.o=.d)

.PHONY: all

all: ${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CC} ${LFLAGS} ${OBJECTS} -o $@ >> sdsoc.log

%.o: %.cpp
	${CC} ${CFLAGS} $< -o $@ > sdsoc.log

clean:
	${RM} ${EXECUTABLE} ${OBJECTS} *.d 

csim:
	vivado_hls csim.tcl
sw:
	g++ -O3 ${APPSOURCES} 

ultraclean: clean
	${RM} ${EXECUTABLE}.bit  
	${RM} -rf _sds sd_card hls.prj
	${RM} sdsoc.log vivado_hls.log
