cmake_minimum_required(VERSION 3.25)
project(Lab11Qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/qt6/bin")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Lab11Qt main.cpp
        entities/medicament.h
        entities/medicament.cpp
        entities/medicament_validator.h
        entities/medicament_validator.cpp
        entities/reteta.h
        entities/reteta.cpp
        exceptions/exceptions.h
        exceptions/exceptions.cpp
        repository/repo.cpp
        repository/repo.h
        repository/reteta_repo.cpp
        repository/reteta_repo.h
        services/service_validateInput.h
        services/service_crud.cpp
        services/service_crud.h
        services/service_reteta.cpp
        services/service_reteta.h
        services/service_statistics.h
        services/service_validateInput.cpp
        services/service_statistics.cpp
        tests/test_validatorMedicament.h tests/test_validatorMedicament.cpp tests/test_validateInput.h tests/test_validateInput.cpp tests/test_serviceReteta.h tests/test_serviceReteta.cpp tests/test_serviceCRUD.h tests/test_serviceCRUD.cpp tests/test_service_statistics.h tests/test_service_statistics.cpp tests/test_reteta_repo.h tests/test_reteta_repo.cpp tests/test_reteta.h tests/test_reteta.cpp tests/test_repo.h tests/test_repo.cpp tests/test_entitate.h tests/test_entitate.cpp tests/test_all.h tests/test_all.cpp UI/UI.cpp UI/UI.h UI/DialogAdd.cpp UI/DialogAdd.h UI/DialogDelete.cpp UI/DialogDelete.h UI/DialogModify.cpp UI/DialogModify.h UI/UIGenerare.cpp UI/UIGenerare.h UI/WindowAfisare.cpp UI/WindowAfisare.h UI/DialogFiltrare.h UI/DialogFiltrare.cpp UI/DialogAdaugaCos.h UI/DialogAdaugaCos.cpp UI/UiCos.h UI/UiCos.cpp UI/UiExport.h UI/UiExport.cpp)

target_link_libraries(Lab11Qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

