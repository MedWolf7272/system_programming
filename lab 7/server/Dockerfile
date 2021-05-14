FROM centos
RUN yum update -y
RUN yum install gcc-c++ -y
COPY server.cpp .
RUN g++ server.cpp -o server
CMD ./server 5555

