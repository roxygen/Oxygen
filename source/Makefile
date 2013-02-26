#####################
#       THX@@AI     #
#####################
NAME = oxygen
 
C_SRC = ini/ini.c
CXX_SRC =  CEvent.cpp CApp.cpp main.cpp \
CUtil.cpp ini/INIReader.cpp \
CImage.cpp CImageManager.cpp \
CProcessManager.cpp process/CProcessMove.cpp process/CProcessAlpha.cpp \
CState.cpp CStateManager.cpp state/CStateIntro.cpp state/CStateGame.cpp state/CStateTitle.cpp 
#state/CStateMenu.cpp
OBJ = $(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o)
# that fileextentions of you. They are .cpp, not .cxx.
# also, substitution for ini/ini.c, which needs separate variable
# to be substituted without tambourine dances and blood of innocent virgins
# because Make is shit
 
SDL_CFLAGS = `sdl-config --cflags`
# cflags to cflags
 
SDL_LDFLAGS = `sdl-config --libs`
# libs to ldflags
 
CFLAGS += -Wall -pedantic -O2 $(SDL_CFLAGS)
# -Wall activates most of warnings
 
CXXFLAGS += $(CFLAGS) 
# flags for CXX are analogous to them of CC
 
LDFLAGS += $(SDL_LDFLAGS) -lGL -lGLU -lSDL_image -llua
# expand SDL_LDFLAGS in here
# also all the libs that not directly belong to SDL are better to be
# placed here than into SDL_LDFLAGS
 
.PHONY: all comp clean re
# pseudotarget for Make to not treat theese targets as files to be made
# but as targets
 
all: comp
 
comp: $(OBJ)
	$(CXX) $? -o $(NAME) $(LDFLAGS)
 
clean:
	@-rm $(OBJ)
# there's really no need for -rf keys
 
re: clean all
