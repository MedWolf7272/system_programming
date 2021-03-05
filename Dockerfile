FROM centos
COPY bash_script_ada.sh .
RUN chmod ugo+x bash_script_ada.sh
CMD ./bash_script_ada.sh

