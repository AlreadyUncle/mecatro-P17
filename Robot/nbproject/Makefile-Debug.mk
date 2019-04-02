#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/components/AX12.o \
	${OBJECTDIR}/src/components/LCD.o \
	${OBJECTDIR}/src/components/US_sensor.o \
	${OBJECTDIR}/src/components/kangaroo.o \
	${OBJECTDIR}/src/components/serialport.o \
	${OBJECTDIR}/src/robot/Robot.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot ${OBJECTFILES} ${LDLIBSOPTIONS} -lwiringPi -lwiringPiDev

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/components/AX12.o: src/components/AX12.cpp
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/components/AX12.o src/components/AX12.cpp

${OBJECTDIR}/src/components/LCD.o: src/components/LCD.cpp
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/components/LCD.o src/components/LCD.cpp

${OBJECTDIR}/src/components/US_sensor.o: src/components/US_sensor.cpp
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/components/US_sensor.o src/components/US_sensor.cpp

${OBJECTDIR}/src/components/kangaroo.o: src/components/kangaroo.cpp
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/components/kangaroo.o src/components/kangaroo.cpp

${OBJECTDIR}/src/components/serialport.o: src/components/serialport.cpp
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/components/serialport.o src/components/serialport.cpp

${OBJECTDIR}/src/robot/Robot.o: src/robot/Robot.cpp
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/Robot.o src/robot/Robot.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
