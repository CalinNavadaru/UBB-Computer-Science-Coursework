cmake_minimum_required(VERSION 3.25)
project(LAB12QT)

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

add_executable(LAB12QT main.cpp entities/medicament.cpp entities/medicament_validator.cpp entities/reteta.cpp exceptions/exceptions.cpp repository/repo.cpp repository/reteta_repo.cpp services/service_crud.cpp services/service_reteta.cpp services/service_statistics.cpp services/service_validateInput.cpp tests/test_all.cpp tests/test_entitate.cpp tests/test_repo.cpp tests/test_reteta.cpp tests/test_reteta_repo.cpp tests/test_service_statistics.cpp tests/test_serviceCRUD.cpp tests/test_serviceReteta.cpp tests/test_validateInput.cpp tests/test_validatorMedicament.cpp UI/DialogAdaugaCos.cpp UI/DialogAdd.cpp UI/DialogDelete.cpp UI/DialogFiltrare.cpp UI/DialogModify.cpp UI/UI.cpp UI/UiCos.cpp UI/UiExport.cpp UI/UIGenerare.cpp UI/WindowAfisare.cpp UI/UiCosReadOnly.h UI/UiCosReadOnly.cpp UI/Observer.h UI/Observer.cpp)
target_link_libraries(LAB12QT
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

