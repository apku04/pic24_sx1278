#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/usb/example_mcc_usb_cdc.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/traps.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c mcc_generated_files/spi1.c mcc_generated_files/ext_int.c src/driver/sx1278.c src/driver/timerdriver.c src/driver/usbdriver.c src/protocol/maclayer.c src/protocol/networklayer.c src/system/ringBuffer.c src/system/terminal.c src/main.c src/hal.c src/debugprint.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/ext_int.o ${OBJECTDIR}/src/driver/sx1278.o ${OBJECTDIR}/src/driver/timerdriver.o ${OBJECTDIR}/src/driver/usbdriver.o ${OBJECTDIR}/src/protocol/maclayer.o ${OBJECTDIR}/src/protocol/networklayer.o ${OBJECTDIR}/src/system/ringBuffer.o ${OBJECTDIR}/src/system/terminal.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/hal.o ${OBJECTDIR}/src/debugprint.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/spi1.o.d ${OBJECTDIR}/mcc_generated_files/ext_int.o.d ${OBJECTDIR}/src/driver/sx1278.o.d ${OBJECTDIR}/src/driver/timerdriver.o.d ${OBJECTDIR}/src/driver/usbdriver.o.d ${OBJECTDIR}/src/protocol/maclayer.o.d ${OBJECTDIR}/src/protocol/networklayer.o.d ${OBJECTDIR}/src/system/ringBuffer.o.d ${OBJECTDIR}/src/system/terminal.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/hal.o.d ${OBJECTDIR}/src/debugprint.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/ext_int.o ${OBJECTDIR}/src/driver/sx1278.o ${OBJECTDIR}/src/driver/timerdriver.o ${OBJECTDIR}/src/driver/usbdriver.o ${OBJECTDIR}/src/protocol/maclayer.o ${OBJECTDIR}/src/protocol/networklayer.o ${OBJECTDIR}/src/system/ringBuffer.o ${OBJECTDIR}/src/system/terminal.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/hal.o ${OBJECTDIR}/src/debugprint.o

# Source Files
SOURCEFILES=mcc_generated_files/usb/example_mcc_usb_cdc.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/traps.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c mcc_generated_files/spi1.c mcc_generated_files/ext_int.c src/driver/sx1278.c src/driver/timerdriver.c src/driver/usbdriver.c src/protocol/maclayer.c src/protocol/networklayer.c src/system/ringBuffer.c src/system/terminal.c src/main.c src/hal.c src/debugprint.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GB002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GB002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o: mcc_generated_files/usb/example_mcc_usb_cdc.c  .generated_files/flags/default/9658196483f74e410cdd5b1fca39ad0bbe9cc7 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/207c8794b970a30a3eb7c24f5f21afcc8c83f0d4 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/459fb51251046dd5431eacdb2fba69c616dc7692 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/5708ff6527114001018f75beb77176c3d87aa608 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/d55411929b70f55d06f70978098917eacd798ee4 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/65a591f725d875de8a7dae24b3788d03fa1e9116 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/cbc56d23d23ab221a6fa3f858e596f4fbd89c4bb .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/fab656764c757ea30eefe219f96e2cd1b5d14ba7 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/db30a15d8ca467b42a3bc8615aac64546cd7256d .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/9625d54c8333c1fd0a11a1739366207366e5690f .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/d893018418055f6e80292d0b48dc6cef2d8f7396 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/9cbbbddeee18af35bfab3d1a7c9ec9a0f34e437f .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/5734b8fa913542b61fb706bc8207a46b2f2f9dc0 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/a203661fc452227a2302995e14bbbe0a417f1b93 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/2159bd84c847cd711e66d55609e02d33b6ed568f .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/ext_int.o: mcc_generated_files/ext_int.c  .generated_files/flags/default/3539e124e8c217390921ee08cf4d1b75d6411a26 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ext_int.c  -o ${OBJECTDIR}/mcc_generated_files/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/ext_int.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/sx1278.o: src/driver/sx1278.c  .generated_files/flags/default/8b56fb8faad52810b3ce45ad5a6df449d399a123 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/sx1278.o.d 
	@${RM} ${OBJECTDIR}/src/driver/sx1278.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/sx1278.c  -o ${OBJECTDIR}/src/driver/sx1278.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/sx1278.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/timerdriver.o: src/driver/timerdriver.c  .generated_files/flags/default/10587d9110d65e5bf3035a2126ab78711a1ee300 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/timerdriver.o.d 
	@${RM} ${OBJECTDIR}/src/driver/timerdriver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/timerdriver.c  -o ${OBJECTDIR}/src/driver/timerdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/timerdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/usbdriver.o: src/driver/usbdriver.c  .generated_files/flags/default/e8cabbdfd1162887aa807a9bbe376e7f99178bf8 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/usbdriver.o.d 
	@${RM} ${OBJECTDIR}/src/driver/usbdriver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/usbdriver.c  -o ${OBJECTDIR}/src/driver/usbdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/usbdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/protocol/maclayer.o: src/protocol/maclayer.c  .generated_files/flags/default/e43876f378cead4793ce878ef64be51768d17882 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/protocol" 
	@${RM} ${OBJECTDIR}/src/protocol/maclayer.o.d 
	@${RM} ${OBJECTDIR}/src/protocol/maclayer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/protocol/maclayer.c  -o ${OBJECTDIR}/src/protocol/maclayer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/protocol/maclayer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/protocol/networklayer.o: src/protocol/networklayer.c  .generated_files/flags/default/b1e76444645d04f068e61c49a168ce77c53b2bea .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/protocol" 
	@${RM} ${OBJECTDIR}/src/protocol/networklayer.o.d 
	@${RM} ${OBJECTDIR}/src/protocol/networklayer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/protocol/networklayer.c  -o ${OBJECTDIR}/src/protocol/networklayer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/protocol/networklayer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/system/ringBuffer.o: src/system/ringBuffer.c  .generated_files/flags/default/cdeedc033221bc8b1fd3ca78c9d4af0cc36d959f .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/system" 
	@${RM} ${OBJECTDIR}/src/system/ringBuffer.o.d 
	@${RM} ${OBJECTDIR}/src/system/ringBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system/ringBuffer.c  -o ${OBJECTDIR}/src/system/ringBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system/ringBuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/system/terminal.o: src/system/terminal.c  .generated_files/flags/default/7b22a0abb8961eafb2661443a758a9b8df570d98 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/system" 
	@${RM} ${OBJECTDIR}/src/system/terminal.o.d 
	@${RM} ${OBJECTDIR}/src/system/terminal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system/terminal.c  -o ${OBJECTDIR}/src/system/terminal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system/terminal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/b10c8d88aae23a5cb81f7850c0583920feb4faf9 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/hal.o: src/hal.c  .generated_files/flags/default/ef6b34c6d8a5959b720488296752dd8d9c5bf469 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hal.o.d 
	@${RM} ${OBJECTDIR}/src/hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal.c  -o ${OBJECTDIR}/src/hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/hal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/debugprint.o: src/debugprint.c  .generated_files/flags/default/9a3f5cb3353d5d43952cb5fe1d2bd1016b56eb66 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/debugprint.o.d 
	@${RM} ${OBJECTDIR}/src/debugprint.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debugprint.c  -o ${OBJECTDIR}/src/debugprint.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/debugprint.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o: mcc_generated_files/usb/example_mcc_usb_cdc.c  .generated_files/flags/default/a1a1ab7ba321f05d16a4cb36b15992b5438987a1 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/f55b8780b4c24d4be686f6914a4720fca97d2a82 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/3758ec4f6c0eff6b681d43c372272c2cd6b44a0 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/6bfd8e022a09a6427e1925c843f6bc84d6427694 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/469a2509836c4d978caf5529ea43ccb46aa40709 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/10f2a0137e603f5c403767f49f74727c50e8d5e1 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/eec6b7d41015228aaeaedd737b5eda7f23c8fbac .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/d713cd361e8c74162d0928109ea7bd2153e81185 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/7468220a356305f8ecbd4cee305e55b02de60c1d .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/ef34e535f17363260e53067fadf7488c7cc629d1 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/f1123d78106a8038e50070ef096dbcc80e190be1 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/1a7e65541d312d850cf6cc6ed9127812d01ad357 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/397d706d53bcffc264ee8bad8403875c2df0153 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/fba2ac658610e132b7686b8249efaef4e665822c .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/1683d2fc24bbff298ac81a0450171ae0339f0a85 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/ext_int.o: mcc_generated_files/ext_int.c  .generated_files/flags/default/7a73ebadc414804eb3552648265d0e0a0c94047a .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ext_int.c  -o ${OBJECTDIR}/mcc_generated_files/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/ext_int.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/sx1278.o: src/driver/sx1278.c  .generated_files/flags/default/2e8440ea3263f2970a448549bf09bbb0dff82d02 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/sx1278.o.d 
	@${RM} ${OBJECTDIR}/src/driver/sx1278.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/sx1278.c  -o ${OBJECTDIR}/src/driver/sx1278.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/sx1278.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/timerdriver.o: src/driver/timerdriver.c  .generated_files/flags/default/60ab070643e7e416758d767dfae06f4616bb06ef .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/timerdriver.o.d 
	@${RM} ${OBJECTDIR}/src/driver/timerdriver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/timerdriver.c  -o ${OBJECTDIR}/src/driver/timerdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/timerdriver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/driver/usbdriver.o: src/driver/usbdriver.c  .generated_files/flags/default/6608a59187c10e211f7a29156b0ef98249e016f4 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/usbdriver.o.d 
	@${RM} ${OBJECTDIR}/src/driver/usbdriver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/usbdriver.c  -o ${OBJECTDIR}/src/driver/usbdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/driver/usbdriver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/protocol/maclayer.o: src/protocol/maclayer.c  .generated_files/flags/default/c71d8cc731c952316610a2fd5ca83f7032832e5b .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/protocol" 
	@${RM} ${OBJECTDIR}/src/protocol/maclayer.o.d 
	@${RM} ${OBJECTDIR}/src/protocol/maclayer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/protocol/maclayer.c  -o ${OBJECTDIR}/src/protocol/maclayer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/protocol/maclayer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/protocol/networklayer.o: src/protocol/networklayer.c  .generated_files/flags/default/1773832d8fc2a7bb828205c1fe62c5ac73993c12 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/protocol" 
	@${RM} ${OBJECTDIR}/src/protocol/networklayer.o.d 
	@${RM} ${OBJECTDIR}/src/protocol/networklayer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/protocol/networklayer.c  -o ${OBJECTDIR}/src/protocol/networklayer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/protocol/networklayer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/system/ringBuffer.o: src/system/ringBuffer.c  .generated_files/flags/default/ebb4f3566889e233b4ae0b9b934adbacba1c2081 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/system" 
	@${RM} ${OBJECTDIR}/src/system/ringBuffer.o.d 
	@${RM} ${OBJECTDIR}/src/system/ringBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system/ringBuffer.c  -o ${OBJECTDIR}/src/system/ringBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system/ringBuffer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/system/terminal.o: src/system/terminal.c  .generated_files/flags/default/9efbeb2171f9dc6d1638f7d8070bb772439dd37 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src/system" 
	@${RM} ${OBJECTDIR}/src/system/terminal.o.d 
	@${RM} ${OBJECTDIR}/src/system/terminal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system/terminal.c  -o ${OBJECTDIR}/src/system/terminal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system/terminal.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/8b37812b68fdfaa7be80f767790b75b952fe56a3 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/hal.o: src/hal.c  .generated_files/flags/default/c4209f20ee7ca53e6d74d0820f73b7d287234e74 .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hal.o.d 
	@${RM} ${OBJECTDIR}/src/hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal.c  -o ${OBJECTDIR}/src/hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/hal.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/debugprint.o: src/debugprint.c  .generated_files/flags/default/79171c30453ab3bcd21ca4859b68403f29e89ddb .generated_files/flags/default/3a60306d929cd76682dbf87396049a279970adbd
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/debugprint.o.d 
	@${RM} ${OBJECTDIR}/src/debugprint.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debugprint.c  -o ${OBJECTDIR}/src/debugprint.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/debugprint.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--heap=256,--stack=256,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/com.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/com.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"src/driver" -I"src/protocol" -I"src/system" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"mcc_generated_files/usb/utilities" -I"src" -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=256,--stack=256,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/com.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
