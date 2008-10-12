#
#   LDAP Utilities
#   Copyright (C) 2008 David M. Syzdek <david@syzdek.net>.
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS                                 = po
DIST_SUBDIRS                            = po


# custom directories
localedir				= $(datadir)/locale


# Global flags
AM_LIBS					=
AM_LDADD				= @LTLIBINTL@
AM_LDFLAGS				=
AM_CFLAGS				= $(CFLAGS_WARNINGS)
AM_CPPFLAGS				= $(CFLAGS_WARNINGS) \
					  -I$(top_srcdir)/include \
					  -I$(top_srcdir)/lib \
					  -DLOCALEDIR=\"$(localedir)\" \
					  -DSYSCONFDIR=\"$(sysconfdir)\"
ACLOCAL_AMFLAGS				= -W syntax -W unsupported -W error


# automake targets
bin_PROGRAMS				= src/ldap2csv
noinst_PROGRAMS				= src/ldapconftest
man_MANS				=


# macros for ldap2csv
src_ldap2csv_DEPENDENCIES		= Makefile
src_ldap2csv_CPPFLAGS			= -DPROGRAM_NAME="\"ldap2csv\"" $(AM_CPPFLAGS)
src_ldap2csv_CFLAGS			= $(AM_CFLAGS)
src_ldap2csv_LDFLAGS			= $(AM_LDFLAGS)
src_ldap2csv_LDADD			= $(AM_LDADD) -lldap
src_ldap2csv_SOURCES			= \
					  include/ldap-utils.h \
					  src/ldap2csv.c \
					  src/ldaputils_config.c \
					  src/ldaputils_config.h \
					  src/ldaputils_config_opts.c \
					  src/ldaputils_config_opts.h \
					  src/ldaputils_ldap.c \
					  src/ldaputils_ldap.h


# macros for ldapconftest
src_ldapconftest_DEPENDENCIES		= Makefile
src_ldapconftest_CPPFLAGS		= -DPROGRAM_NAME="\"ldapconftest\"" $(AM_CPPFLAGS)
src_ldapconftest_CFLAGS			= $(AM_CFLAGS)
src_ldapconftest_LDFLAGS		= $(AM_LDFLAGS)
src_ldapconftest_LDADD			= $(AM_LDADD) -lldap
src_ldapconftest_SOURCES		= \
					  include/ldap-utils.h \
					  src/ldapconftest.c \
					  src/ldaputils_config.c \
					  src/ldaputils_config.h \
					  src/ldaputils_config_opts.c \
					  src/ldaputils_config_opts.h


# miscellaneous lists
CLEANFILES				= $(builddir)/a.out        $(srcdir)/a.out \
                                          $(builddir)/*/a.out      $(srcdir)/*/a.out \
					  $(builddir)/config.h.in~ $(srcdir)/config.h.in~ \
					  $(builddir)/po/stamp-po  $(srcdir)/po/stamp-po\
					  $(builddir)/stamp-vti    $(srcdir)/stamp-vti \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip
EXTRA_DIST				=
EXTRA_PROGRAMS				=
EXTRA_TEXINFOS				=
TESTS					=
XFAIL_TESTS				=


# substitution routine
do_subst = sed \
		-e 's,[@]configure_input[@],${@}. Generated from ${@}.in by make.,g' \
		-e 's,[@]SHELL[@],@SHELL@,g' \
		-e 's,[@]PACKAGE_VERSION[@],@PACKAGE_VERSION@,g' \
		-e 's![@]PACKAGE_NAME[@]!@PACKAGE_NAME@!g' \
		-e 's,[@]PACKAGE_TARNAME[@],@PACKAGE_TARNAME@,g' \
		-e 's,[@]PACKAGE_BUGREPORT[@],@PACKAGE_BUGREPORT@,g' \
		-e 's,[@]PACKAGE_COPYRIGHT[@],@PACKAGE_COPYRIGHT@,g' \
		-e 's,[@]RELEASE_MONTH[@],@RELEASE_MONTH@,g'
do_subst_fn = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0644 ${@}
do_subst_dt = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0644 ${@}


# custom targets


# local targets
install-exec-local:

install-data-local:

install-exec-hook:

install-data-hook:

uninstall-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

# end of automake file