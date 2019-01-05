#Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++0x
#CXXFLAGS += -Wall
#CXXFLAGS += -pedantic-errors
#CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time

#Project executable output file
PROJ = final

#Object files
OBJS = main.o menu.o BeastCell.o CargoStorage.o Game.o Junction.o PrisonerCell.o Space.o SurveillanceRoom.o WeaponsLocker.o

#Source files
SRCS = main.cpp menu.cpp BeastCell.cpp CargoStorage.cpp Game.cpp Junction.cpp PrisonerCell.cpp Space.cpp SurveillanceRoom.cpp WeaponsLocker.cpp

#Header files
HEADERS = menu.hpp BeastCell.hpp CargoStorage.hpp Game.hpp Junction.hpp PrisonerCell.hpp Space.hpp SurveillanceRoom.hpp WeaponsLocker.hpp

#Compile project executable from object files
${PROJ}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${PROJ}

#Compile object files from source files
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

#Remove project executable and object files
clean:
	rm ${PROJ} ${OBJS}

#Citation:
#Format of this makefile based off of: http://web.engr.oregonstate.edu/~rookert/cs162/03.mp4