include Makefile.inc

all_subdirs = lib findlib filed console plugins
ifeq ($(BUILD_QTGUI),yes)
all_subdirs += qt-console qt-tray-monitor
endif

all: qt-gui
	@for I in ${all_subdirs}; \
	  do (cd $$I; echo "==>Entering directory `pwd`"; \
		$(MAKE) WIN_VERSION=$(WIN_VERSION) DESTDIR=$(DESTDIR) $@ || (echo ""; echo ""; echo "  ====== Error in `pwd` ======"; \
		echo ""; echo ""; exit 1;)); \
	done

install:
	@for I in ${all_subdirs}; \
	  do (cd $$I; echo "==>Entering directory `pwd`"; \
		$(MAKE) WIN_VERSION=$(WIN_VERSION) DESTDIR=$(DESTDIR) $@ || (echo ""; echo ""; echo "  ====== Error in `pwd` ======"; \
		echo ""; echo ""; exit 1;)); \
	done

clean:
	@for I in ${all_subdirs}; \
	  do (cd $$I; echo "==>Entering directory `pwd`"; \
		$(MAKE) WIN_VERSION=$(WIN_VERSION) DESTDIR=$(DESTDIR) $@ || (echo ""; echo ""; echo "  ====== Error in `pwd` ======"; \
		echo ""; echo ""; exit 1;)); \
	done

distclean:
	@for I in ${all_subdirs}; \
	  do (cd $$I; echo "==>Entering directory `pwd`"; \
		$(MAKE) WIN_VERSION=$(WIN_VERSION) DESTDIR=$(DESTDIR) $@ || (echo ""; echo ""; echo "  ====== Error in `pwd` ======"; \
		echo ""; echo ""; exit 1;)); \
	done

ifeq ($(BUILD_QTGUI),)
qt-gui:
else
qt-gui: qt-console/Makefile qt-tray-monitor/Makefile

qt-console/Makefile: qt-console/bat.pro
	cd qt-console; $(QMAKE) bat.pro

qt-tray-monitor/Makefile: qt-tray-monitor/tray-monitor.pro
	cd qt-tray-monitor; $(QMAKE) tray-monitor.pro
endif
