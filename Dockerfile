FROM gcc:latest

WORKDIR /workspace

COPY . /workspace

RUN g++ -o my_program main.cpp

CMD ["./my_program"]