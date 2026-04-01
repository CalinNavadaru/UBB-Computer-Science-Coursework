cmake_minimum_required(VERSION 3.25)
project(lab6_7)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab6_7 main.cpp entities/medicament.cpp entities/medicament.h tests/test_entitate.cpp tests/test_entitate.h tests/test_all.cpp tests/test_all.h repository/repo.cpp repository/repo.h exceptions/exceptions.cpp exceptions/exceptions.h tests/test_repo.cpp tests/test_repo.h services/service_crud.cpp services/service_crud.h ui/ui.cpp ui/ui.h tests/test_serviceCRUD.cpp tests/test_serviceCRUD.h "../lab6-7 (copy)/vectordinamic.h" services/service_statistics.cpp services/service_statistics.h tests/test_service_statistics.cpp tests/test_service_statistics.h entities/medicament_validator.cpp entities/medicament_validator.h repository/reteta.cpp repository/reteta.h services/service_reteta.cpp services/service_reteta.h ui/ui_reteta.cpp ui/ui_reteta.h ui/ui_principal.cpp ui/ui_principal.h tests/test_validatorMedicament.cpp tests/test_validatorMedicament.h tests/test_reteta.cpp tests/test_reteta.h tests/test_serviceReteta.cpp tests/test_serviceReteta.h)
