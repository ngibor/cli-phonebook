cmake_minimum_required(VERSION 3.17)
project(untitled C)

set(CMAKE_C_STANDARD 11)


add_executable(untitled main.c UserInterface.c UserInterface.h Authentication.c Authentication.h Phonebook.c Phonebook.h Constants.h)
set(OPENSSL_USE_STATIC_LIBS FALSE)
set(OPENSSL_ROOT_DIR /usr/include/openssl)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)