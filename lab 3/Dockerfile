FROM centos
RUN yum update -y
RUN yum install gcc-c++ -y
COPY . .
RUN g++ main.cpp -masm=intel
CMD ./a.out
