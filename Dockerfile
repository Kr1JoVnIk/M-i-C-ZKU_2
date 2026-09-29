FROM gcc:latest
WORKDIR /app
COPY task2.cpp ./
RUN g++ -std=c++17 -O2 -o task2 task2.cpp
CMD ["./task2"]