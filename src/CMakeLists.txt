AUX_SOURCE_DIRECTORY(. DIR_SENSORDB_API_SRCS)
FIND_PACKAGE(Qt5Sql REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
ADD_LIBRARY (${SENSORDB_API_LIB} STATIC ${DIR_SENSORDB_API_SRCS})
qt5_use_modules(SensorDB_API  Widgets Sql Core)
qt5_use_modules(SensorDB_API  Widgets Sql Core)

#zhangxaochen:
find_package( Boost 1.54.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${Qt5Core_INCLUDES})
include_directories(${Qt5Sql_INCLUDES})

ADD_LIBRARY (${SENSORDB_API_LIB}_shared SHARED ${DIR_SENSORDB_API_SRCS})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

