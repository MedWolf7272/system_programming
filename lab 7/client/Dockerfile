FROM centos
RUN yum update -y
RUN yum install gcc-c++ -y
COPY client.cpp .
RUN g++ client.cpp -o client
CMD ./client hostname 5555

