CXX = g++

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

UI_OBJS = ui/Element.o ui/Decorator.o ui/Decorators.o \
	ui/Drawable.o ui/UpdateInfo.o ui/State.o ui/Factory.o \

OBJS = App.o main.o $(UI_OBJS)

gsx: $(OBJS)
	$(CXX) $(OBJS) -o gsx $(LIBS)

main.o: main.cpp
	$(CXX) -c main.cpp 

Element.o: Element.h Element.cpp UpdateInfo.h
	$(CXX) -c Element.cpp

Decorator.o: Decorator.h Decorator.cpp Element.h
	$(CXX) -c Decorator.cpp

Decorators.o: Decorators.h Decorators.cpp Decorator.h
	$(CXX) -c Decorators.cpp

Drawable.o: Drawable.h Drawable.cpp Element.h
	$(CXX) -c Drawable.cpp

UpdateInfo.o: UpdateInfo.h UpdateInfo.cpp
	$(CXX) -c UpdateInfo.cpp

Factory.o: Factory.h Factory.cpp Decorators.h
	$(CXX) -c Factory.cpp

State.o: State.h State.cpp Element.h
	$(CXX) -c State.cpp

App.o: App.h App.cpp ui/State.h
	$(CXX) -c App.cpp

clean:
	rm $(OBJS) gsx
