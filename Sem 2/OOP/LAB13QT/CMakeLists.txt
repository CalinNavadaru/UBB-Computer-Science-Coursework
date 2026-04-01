cmake_minimum_required(VERSION 3.25)
project(LAB13QT)

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

add_executable(LAB13QT main.cpp services/service_reteta.cpp entities/reteta.cpp entities/medicament.cpp exceptions/exceptions.cpp repository/repo.cpp entities/medicament_validator.cpp tests/test_entitate.cpp services/service_crud.cpp services/service_validateInput.cpp tests/test_repo.cpp tests/test_all.cpp services/service_statistics.cpp repository/reteta_repo.cpp tests/test_reteta.cpp tests/test_reteta_repo.cpp tests/test_service_statistics.cpp tests/test_serviceCRUD.cpp tests/test_serviceReteta.cpp tests/test_validateInput.cpp tests/test_validatorMedicament.cpp UI/DialogAdaugaCos.cpp UI/DialogAdaugaCos.h UI/DialogAdd.cpp UI/DialogAdd.h UI/DialogDelete.cpp UI/DialogFiltrare.cpp UI/DialogDelete.h UI/WindowAfisare.h UI/WindowAfisare.cpp UI/UIGenerare.h UI/UIGenerare.cpp UI/UiExport.h UI/UiExport.cpp UI/UiCosReadOnly.h UI/UiCosReadOnly.cpp UI/UiCos.h UI/UiCos.cpp UI/UI.cpp UI/Observer.cpp UI/DialogModify.h UI/DialogModify.cpp UI/DialogFiltrare.h UI/ModelTable.h UI/ModelTable.cpp UI/ModelLista.h UI/ModelLista.cpp UI/ModelWindowAfisare.h UI/ModelWindowAfisare.cpp)
target_link_libraries(LAB13QT
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

