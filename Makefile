

build:
	gcc window.c -o window  -lglfw   -lglut -lGL -lGLEW -lGLU -Wall # -lGL -lglfw3 -lXrandr -lglfw -lXi -lX11 -lXxf86vm -lpthread 
	./glew
	