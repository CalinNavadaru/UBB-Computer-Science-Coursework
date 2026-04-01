cmake_minimum_required(VERSION 3.24)
project(lab02 C)

set(CMAKE_C_STANDARD 11)

set(PROJECT_HEADERS
        entities/HEADERS/validator.h
        entities/HEADERS/entities.h
        repository/HEADERS/repo.h
        service/HEADERS/service.h
        tests/HEADERS/test_entity.h
        tests/HEADERS/test_validator.h
        ui/ui.h)

set(PROJECT_SOURCES
        entities/SOURCE_FILES/validator.c
        entities/SOURCE_FILES/entities.c
        repository/SOURCE_FILES/repo.c
        service/SOURCE_FILES/service.c
        tests/SOURCE_FILES/test_entity.c
        tests/SOURCE_FILES/test_validator.c
        ui/ui.c)


add_executable(lab02 main.c ${PROJECT_SOURCES} ${PROJECT_HEADERS})
