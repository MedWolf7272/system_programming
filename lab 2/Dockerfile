FROM centos
RUN yum update -y
RUN yum install nasm gcc-c++ -y
COPY . .
RUN nasm -f elf64 -o lab2.o main.s
RUN gcc -m64 -no-pie lab2.o -o lab2_ab
RUN g++ main.cpp -o lab2_pp
CMD ./lab2_ab && ./lab2_pp

