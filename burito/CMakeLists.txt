
cmake_minimum_required(VERSION 3.0)
project(labtest)

set(OBJ_SRC_FILES
  src/App.cpp
  src/BaseBurito.cpp
  src/BuritoFactory.cpp
  src/ComboDiscount.cpp
  src/Decorator.cpp
  src/Drink.cpp
  src/Fries.cpp
  src/Jumbo.cpp
  src/Sausage.cpp
  src/SetDiscount.cpp
  src/Transaction.cpp
  src/TransactionManager.cpp
  )

set(OBJ_HEADER_FILES
  src/App.h
  src/BaseBurito.h
  src/Burito.h
  src/BuritoFactory.h
  src/ComboDiscount.h
  src/Decorator.h
  src/Drink.h
  src/Fries.h
  src/Jumbo.h
  src/Sausage.h
  src/SetDiscount.h
  src/Transaction.h
  src/TransactionManager.h
  )


add_executable(labtest src/main.cpp ${OBJ_SRC_FILES} ${OBJ_HEADER_FILES})
source_group(headers FILES ${OBJ_HEADER_FILES})

if (MSVC)
  target_compile_options(labtest PRIVATE "/utf-8")
endif()
