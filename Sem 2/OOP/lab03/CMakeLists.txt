cmake_minimum_required(VERSION 3.24)
project(lab03 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab03 main.c entities/HEADERS/entities.h entities/SOURCES/entities.c tests/HEADERS/test_entity.h tests/SOURCES/test_entity.c entities/HEADERS/validator.h entities/SOURCES/validator.c tests/HEADERS/test_validator.h tests/SOURCES/test_validator.c repository/SOURCES/repo.c repository/HEADERS/repo.h tests/SOURCES/test_repo.c tests/HEADERS/test_repo.h service/SOURCES/service.c service/HEADERS/service.h ui/SOURCES/ui.c ui/HEADERS/ui.h tests/SOURCES/test_all.c tests/HEADERS/test_all.h service/SOURCES/validator_input.c service/HEADERS/validator_input.h service/SOURCES/service_statistici.c service/HEADERS/service_statistici.h tests/SOURCES/test_service.c tests/HEADERS/test_service.h tests/SOURCES/test_service_statistici.c tests/HEADERS/test_service_statistici.h tests/SOURCES/test_validator_input.c tests/HEADERS/test_validator_input.h)
