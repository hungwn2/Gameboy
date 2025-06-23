cmake_minimum_required(VERSION 3.10)
project(MessagingApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find Dependencies ---
# You need to have these libraries installed on your system.
# On Debian/Ubuntu: sudo apt-get install libpqxx-dev libjsoncpp-dev libboost-system-dev
# On macOS (Homebrew): brew install postgresql libpqxx jsoncpp boost

find_package(libpqxx REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(jsoncpp REQUIRED)

# --- Add Crow library ---
# It's often easiest to add Crow as a subdirectory or using FetchContent
# For simplicity, we assume you have cloned crow into a 'lib/crow' folder
add_subdirectory(lib/crow) # Assuming crow is in a 'lib' folder

# --- Define Executable ---
add_executable(messaging_app
    main.cpp
    Database.cpp
    WebSocketManager.cpp
    Auth.cpp
)

# --- Link Libraries ---
target_link_libraries(messaging_app PRIVATE
    Crow::crow # Crow's own target
    ${LIBPQXX_LIBRARIES}
    jsoncpp
    Threads::Threads
    Boost::system
)

# --- Include Directories ---
target_include_directories(messaging_app PRIVATE
    ${LIBPQXX_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)