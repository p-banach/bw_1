cmake_minimum_required(VERSION 3.10)
project(kombaIIn)

set(CMAKE_CXX_STANDARD 17)
LINK_LIBRARIES(libstdc++fs.a)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17   -static")
add_executable( kombaIIn main.cpp base64.cpp base64.h constants.h mail.cpp mail.h
                paragon.cpp paragon.h klient.cpp klient.h produkt.cpp produkt.h
                utilities.cpp utilities.h konfiguracja.cpp konfiguracja.h
                powiadomienia.cpp powiadomienia.h tabela.cpp tabela.h)