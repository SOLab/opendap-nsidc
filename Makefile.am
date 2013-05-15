
# Automake file for binary_ssmi_nsidc-handler
#
# 5/17/2005 jhrg
#
# $Id: Makefile.am 12972 2006-01-05 15:41:07Z pwest $

AUTOMAKE_OPTIONS = foreign check-news

ACLOCAL_AMFLAGS = -I conf

lib_besdir=$(libdir)/bes
lib_bes_LTLIBRARIES = libbinary_ssmi_nsidc_module.la
dist_bin_SCRIPTS = bes-binary_ssmi_nsidc-data.sh

NSIDC_SRCS:=

NSIDC_HDRS:=

BES_SRCS = \
		NSIDCModule.cc NSIDCRequestHandler.cc NSIDCVariable.cc NSIDCArray.cc NSIDCUtils.cc \
                NSIDCDAS.cc NSIDCDDS.cc NSIDCGridCoordinatesLat.cc NSIDCGridCoordinatesLon.cc

BES_HDRS = \
		NSIDCModule.h NSIDCRequestHandler.h \
		NSIDCResponseNames.h NSIDCVariable.h NSIDCArray.h NSIDCUtils.h \
                NSIDCDAS.h NSIDCDDS.h NSIDCGridCoordinates.h

libbinary_ssmi_nsidc_module_la_SOURCES = $(NSIDC_SRCS) $(BES_SRCS) $(NSIDC_HDRS) $(BES_HDRS)
libbinary_ssmi_nsidc_module_la_CPPFLAGS = $(BES_CPPFLAGS)
libbinary_ssmi_nsidc_module_la_LDFLAGS = -avoid-version -module 
libbinary_ssmi_nsidc_module_la_LIBADD = $(BES_LIBS)

EXTRA_PROGRAMS = 

EXTRA_DIST = COPYRIGHT COPYING bes-binary_ssmi_nsidc-data.sh.in binary_ssmi_nsidc_module.spec

CLEANFILES = *~ bes-binary_ssmi_nsidc-data.sh

do_subst = sed -e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		   	   -e 's,[@]libdir[@],$(libdir),g' \
		   	   -e 's,[@]datadir[@],$(datadir),g'

bes-binary_ssmi_nsidc-data.sh: bes-binary_ssmi_nsidc-data.sh.in config.status
	$(do_subst) < $(srcdir)/bes-binary_ssmi_nsidc-data.sh.in > bes-binary_ssmi_nsidc-data.sh
	chmod +x bes-binary_ssmi_nsidc-data.sh

# This makes sure that the handler modifies the bes which configure found
# even when distcheck is run.
bes-conf: bes-binary_ssmi_nsidc-data.sh
	(bes_prefix=`bes-config --prefix` ; \
	if test "$$bes_prefix" = "/usr" ; \
	 then \
	    ./bes-binary_ssmi_nsidc-data.sh /etc/bes/bes.conf /usr/lib/bes ;\
	else \
	    ./bes-binary_ssmi_nsidc-data.sh $$bes_prefix/etc/bes/bes.conf $$bes_prefix/lib/bes ; \
	fi)

###########################################################################
#
# Build linux RPMs

srpm: dist
	rpmbuild -ts binary_ssmi_nsidc_module-@PACKAGE_VERSION@.tar.gz

rpm: dist
	rpmbuild -tb binary_ssmi_nsidc_module-@PACKAGE_VERSION@.tar.gz

###########################################################################

# Build OS/X Packages.

PACKAGEMAKER=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker*

UNIV_ARCH=-arch ppc -arch i386
MAC_SYSROOT=Developer/SDKs/MacOSX10.4u.sdk

PKG_CONF_FLAGS=

clean-pkg:
	-rm -rf mac_osx @PACKAGE@-@PACKAGE_VERSION@.pkg @PACKAGE@-@PACKAGE_VERSION@

pkg-build:
	./configure --prefix=/usr --disable-dependency-tracking $(PKG_CONF_FLAGS)
	make clean all
	DESTDIR=${PWD}/mac_osx make install

pkg-main:
	./OSX_Resources/update_mac_package_contents.pl README "configure.ac" "mac_osx/usr"
	${PACKAGEMAKER} -build -p @PACKAGE@-@PACKAGE_VERSION@.pkg \
		-f mac_osx/usr \
		-ds -r OSX_Resources \
		-i OSX_Resources/Info.plist \
		-d OSX_Resources/Description.plist
	-rm -rf mac_osx

pkg-dmg:
	-rm -rf @PACKAGE@-@PACKAGE_VERSION@
	-rm -rf @PACKAGE@-@PACKAGE_VERSION@.dmg
	mkdir @PACKAGE@-@PACKAGE_VERSION@
	mv @PACKAGE@-@PACKAGE_VERSION@.pkg @PACKAGE@-@PACKAGE_VERSION@
	cp README NEWS @PACKAGE@-@PACKAGE_VERSION@
	dropdmg -i --sanitize-for-servers --format zlib @PACKAGE@-@PACKAGE_VERSION@
	-rm -rf @PACKAGE@-@PACKAGE_VERSION@

pkg: clean-pkg pkg-build pkg-main pkg-dmg

