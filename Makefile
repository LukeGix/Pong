build:
	 g++ \
	 Game.cpp \
	 Game.h \
	 Main.cpp \
	-static-libstdc++ \
	-static-libgcc \
	-I"C:\libsdl\include""C:\libsdlmix\include" \
	-L"C:\libsdl\lib""C:\libsdlmix\lib" \
	-lmingw32 \
	-lSDL2_mixer \
	-lSDL2main \
	-lSDL2 \
	-o PongBuild.exe
