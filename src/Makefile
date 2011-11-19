################################
##      Archivo Makefile      ##
################################

# Subdirectorios
ABM = ./Archivos/ArbolBMas/*.cpp
ABQ = ./Archivos/EnBloques/*.cpp
HSH = ./Archivos/Hashing/*.cpp
AUX = ./ClasesAuxiliares/*.cpp
CRI = ./Criptografia/*.cpp
ENT = ./Entidades/*.cpp
LGC = ./Logica/*.cpp
TST = ../tests/*.cpp

# Constantes
NOMBRE_EJECUTABLE = voto												# Nombre del ejecutable
FUENTES = *.cpp $(ABM) $(ABQ) $(HSH) $(AUX) $(CRI) $(ENT) $(LGC) $(TST)	# Enumero los *.cpp existentes
SUBCARPETAS = ClasesAuxiliares											# Subcarpetas donde existan archivos "*.h" que no sean de clases
FLAGSWARN = -Wall -Wextra												# Flags para obtener warnings del compilador g++
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


