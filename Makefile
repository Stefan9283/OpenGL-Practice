

build:
	gcc glew.c -o glew  -lglfw   -lglut -lGL -lGLEW -lGLU -Wall # -lGL -lglfw3 -lXrandr -lglfw -lXi -lX11 -lXxf86vm -lpthread 
	./glew
	