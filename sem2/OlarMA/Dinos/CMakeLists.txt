cmake_minimum_required(VERSION 3.23)
project(Dinosaur)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)
set(CMAKE_CXX_STANDARD 17)

add_executable(Dinosaur main.cpp AssetManager.h AssetManager.cpp DatabaseFunc.cpp DatabaseFunc.h dino.h Graphics.h includes.h LooserMenu.cpp Menu.cpp ProfileMenu.cpp RegisterMenu.cpp RegisterMenu.h Textbox.cpp Textbox.h WinnerMenu.cpp StartMenu.cpp StartBattleMenu.cpp ShopMenu.cpp sqlite3.h sqlite3ext.h sqlite3.c)

target_link_libraries(Dinosaur sfml-graphics)