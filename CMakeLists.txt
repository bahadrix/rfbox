cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME RFBox)

set(${PROJECT_NAME}_BOARD nano)
set(ARDUINO_CPU atmega328)
project(${PROJECT_NAME})

include_directories(lib/ArduinoCore-avr/libraries/SPI/src)
include_directories(lib/RF24)
include_directories(lib/ArduinoCore-avr/libraries/EEPROM/src)
# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS
        util.cpp
        lib/ArduinoCore-avr/libraries/SPI/src/SPI.cpp
        lib/RF24/RF24.cpp
        broker.cpp
        serialcontroller.cpp
        commander.cpp
        systemcommander.cpp
        basiccommander.cpp
        rfbox_test.cpp)
set(${PROJECT_NAME}_HDRS
        util.h
        commander.h
        broker.h
        serialcontroller.h
        systemcommander.h
        basiccommander.h
        lib/ArduinoCore-avr/libraries/EEPROM/src/EEPROM.h
        )

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
# set(${PROJECT_NAME}_SKETCH RFBox.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${PROJECT_NAME}_PORT /dev/cu.usbserial-14220)
# set(nano.upload.speed 9600)

## Verbose build process
# set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
