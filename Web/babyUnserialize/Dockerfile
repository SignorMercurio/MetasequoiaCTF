FROM php:5.6.24-apache

RUN apt-get update

RUN apt install -y curl
RUN apt-get install -y libfreetype6-dev libmcrypt-dev libjpeg-dev libpng-dev
RUN docker-php-ext-configure gd --enable-gd-native-ttf --with-freetype-dir=/usr/include/freetype2 --with-png-dir=/usr/include --with-jpeg-dir=/usr/include
RUN docker-php-ext-install gd
ADD app/ /var/www/html/
RUN chmod -R 777 /var/www/html/uploads
ADD start.sh /start.sh

RUN chmod -R 777 /start.sh
