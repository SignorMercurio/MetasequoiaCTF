FROM alpine
LABEL Author="Tiaonmmn.ZMZ"
COPY files/src/ /var/www/localhost/cgi-bin/
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories &&\
    apk update &&\
    apk add apache2 perl perl-cgi &&\
    sed -i "s:#LoadModule cgi_module modules/mod_cgi.so:LoadModule cgi_module modules/mod_cgi.so:" /etc/apache2/httpd.conf &&\
    rm -rfv /var/www/localhost/cgi-bin/printenv* &&\
    rm -rfv /var/www/localhost/cgi-bin/test-cgi &&\
    mv /var/www/localhost/cgi-bin/index.html /var/www/localhost/htdocs &&\
    chmod +x /var/www/localhost/cgi-bin/*
EXPOSE 80
CMD /usr/sbin/httpd -D FOREGROUND
