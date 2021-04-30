FROM centos
RUN yum update -y
RUN yum install gcc-c++ -y
COPY code.cpp .
RUN g++ code.cpp -o code -lpthread
CMD ./code

