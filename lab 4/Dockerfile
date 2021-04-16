FROM centos
RUN yum update -y
RUN yum install gcc-c++ -y
COPY code.cpp .
COPY child.cpp .
RUN g++ child.cpp -o child
RUN g++ code.cpp -o code
CMD ./code

