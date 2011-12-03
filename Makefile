################################
##      Archivo Makefile      ##
################################

# Subdirectorios
ABM = ./src/Archivos/ArbolBMas/*.cpp
ABQ = ./src/Archivos/EnBloques/*.cpp
HSH = ./src/Archivos/Hashing/*.cpp
AUX = ./src/ClasesAuxiliares/*.cpp
CPT = ./src/Criptografia/*.cpp
ENT = ./src/Entidades/*.cpp
LGC = ./src/Logica/*.cpp
SRC = ./src/*.cpp
TST = ./tests/*.cpp

# Constantes
NOMBRE_EJECUTABLE = voto											# Nombre del ejecutable
FUENTES = $(ABM) $(ABQ) $(HSH) $(AUX) $(CPT) $(ENT) $(LGC) $(SRC) $(TST)	# Enumero los *.cpp existentes
SUBCARPETAS = ClasesAuxiliares										# Subcarpetas donde existan archivos "*.h" que no sean de clases
FLAGSWARN = -Wall -Wextra											# Flags para obtener warnings del compilador g++
FLAGS = -O0 -g3 -fmessage-length=0 -I $(SUBCARPETAS) -o $(NOMBRE_EJECUTABLE)	# Preparo todos los flags para el comando g++


#Objetivo Inicio: Aquí se enumeran todos los objetivos que quiero correr
inicio : main


#Objetivo main: Compilo el programa
main :
	@echo ' '
	@echo 'Compilo para obtener el ejecutable: ' $(NOMBRE_EJECUTABLE)
	@echo ' '
	@echo 'Archivos cpp a compilar: '
	@echo $(FUENTES)
	@echo '-----------------------------------------------'
	@g++ $(FUENTES) $(FLAGS)
	@echo 'Terminó la compilación'
	@echo ' '


