################################
##      Archivo Makefile      ##
################################

# Subdirectorios
ABM = ./Archivos/ArbolBMas/*.cpp
ABQ = ./Archivos/EnBloques/*.cpp
HSH = ./Archivos/Hashing/*.cpp
AUX = ./ClasesAuxiliares/*.cpp
ENT = ./Entidades/*.cpp
LGC = ./Logica/*.cpp
TST = ../tests/*.cpp

# Variables
NOMBRE_EJECUTABLE = voto											# Nombre del ejecutable
FUENTES = *.cpp $(ABM) $(ABQ) $(HSH) $(AUX) $(ENT) $(LGC) $(TST)	# Enumero los *.cpp existentes
SUBCARPETAS = Auxiliares											# Subcarpetas donde existan archivos "*.h" que no sean de clases tipo <head.h>
FLAGS = -I $(SUBCARPETAS) -o $(NOMBRE_EJECUTABLE)					# Preparo todos los flags para el comando g++


#Objetivo Inicio: Aquí se enumeran todos los objetivos que quiero correr
inicio : main

#Objetivo main: Compilo el programa
main :
	@echo ' '
	@echo 'Compilo para obtener el ejecutable: ' $(NOMBRE_EJECUTABLE)
	@echo 'Archivos cpp a compilar: '
	@echo $(FUENTES)
	@echo '-----------------------------------------------'
	@g++ $(FUENTES) $(FLAGS)
	@echo '-----------------------------------------------'
	@echo 'Terminó la compilación'



