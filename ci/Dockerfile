FROM debian:9.2

RUN \
	rm -rf /var/lib/apt/lists; \
	echo "deb ftp://ftp.debian.org/debian/ stretch main contrib non-free" > /etc/apt/sources.list; \
	apt-get update; \
	apt-get upgrade -y; \
	apt-get autoremove -y; \
	apt-get clean

RUN apt-get update; \
	apt-get -y install --fix-missing \
	cmake \
	dbus-x11 \
	git \
	libxss-dev \
	python-dbus \
	python-gobject \
	python-pip \
	qt5-default \
	qtbase5-dev \
	x11proto-scrnsaver-dev

RUN pip install behave

COPY gmock-install.sh /home/root/
RUN /home/root/gmock-install.sh

