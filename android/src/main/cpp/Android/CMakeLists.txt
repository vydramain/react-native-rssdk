# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# configure import libs
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../../../distribution)

add_library(lib_RSNet SHARED IMPORTED)
set_target_properties(lib_RSNet PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libRSNet.so)

add_library(lib_RSPlay SHARED IMPORTED)
set_target_properties(lib_RSPlay PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libRSPlay.so)

add_library(lib_RSSDKWrapper SHARED IMPORTED)
set_target_properties(lib_RSSDKWrapper PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/RSSDKWrapper/Lib/${ANDROID_ABI}/libRSSDKWrapper.so)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

file(GLOB SOURCES
    "../JsonCpp/*.cpp"
    "*.cpp"
)

add_library(SDKWrapper SHARED ${SOURCES})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       SDKWrapper
                       lib_RSNet
                       lib_RSPlay
                       lib_RSSDKWrapper
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})

add_custom_command(TARGET SDKWrapper PRE_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy
                   #"${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libP2PClient.so"
                   #"${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libP2P_TunnelV2_SVN_1.1.0.0.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libIOTCAPIs.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libP2PTunnelAPIs.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libRDTAPIs.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libTUTKGlobalAPIs.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libjson-c.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libt2u.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libRSNet.so"
                   "${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libaudio3a.so"
                   "${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libtensorflow-lite.so"
				   "${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libRSPlay.so"
                   "${distribution_DIR}/RSSDKWrapper/Lib/${ANDROID_ABI}/libRSSDKWrapper.so"
                   "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
