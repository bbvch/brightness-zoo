FROM debian:stretch

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

