cmake_minimum_required(VERSION 3.23)
project(program)

set(CMAKE_CXX_STANDARD 14)


add_executable(program main.cpp Egyesulet.cpp Egyesulet.h Csapattag.cpp Csapattag.h
        Ember.cpp Ember.h Vezetok.cpp Vezetok.h Jatekosok.cpp Jatekosok.h Szemelyzet.cpp Szemelyzet.h String.cpp String.h Ellenorzofuggvenyek.cpp Ellenorzofuggvenyek.h)

add_executable(program1 test.cpp Egyesulet.cpp Egyesulet.h Csapattag.cpp Csapattag.h Ember.cpp Ember.h Vezetok.cpp Vezetok.h
                Jatekosok.cpp Jatekosok.h Szemelyzet.cpp Szemelyzet.h String.cpp String.h Ellenorzofuggvenyek.cpp Ellenorzofuggvenyek.h gtest_lite.h)