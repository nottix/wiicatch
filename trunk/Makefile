INCLUDE = -D_REENTRANT -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/freetype2 -I/usr/include/directfb -I/usr/include/libpng12 -I/usr/include/pixman-1

LIB = -lnotify -lgtk-x11-2.0 -ldbus-glib-1 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lpango-1.0 -lcairo -lgmodule-2.0 -ldl -ldbus-1 -lgobject-2.0 -lglib-2.0

all:
	gcc -Wall -O2 $(INCLUDE) $(LIB) -lcwiid -o wiicatch wiicatch.c
