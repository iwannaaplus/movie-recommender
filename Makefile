CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = app

SRCS = main.cpp Movie.cpp User.cpp Rating.cpp MovieManager.cpp UserManager.cpp RatingManager.cpp SimilarityCalculator.cpp Recommender.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Movie.h User.h Rating.h
Movie.o: Movie.cpp Movie.h
User.o: User.cpp User.h
Rating.o: Rating.cpp Rating.h
MovieManager.o: MovieConstants.h
SimilarityCalculator.o: MovieConstants.h
Recommender.o: MovieConstants.h

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)