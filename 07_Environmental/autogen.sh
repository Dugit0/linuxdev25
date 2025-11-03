#!/usr/bin/env sh
set -e
aclocal
autoconf
# autoheader
automake --add-missing
