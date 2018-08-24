#
#	Root Makefile for Treet++
#
#	Recurse into directories and make target in each
#
#	$Author: rgm $
#	$Date: 2003/01/05 07:32:36 $
#	$Source: /home/sumatra/rgm/CVSROOT/Treet++/Makefile,v $
#	$Id: Makefile,v 1.5 2003/01/05 07:32:36 rgm Exp $
#
#

# Directories to recurs into
DIRS=Src

apps=LispMain

# The default target is all
default: app

app: all
	g++ -ISrc -LSrc -lsib -o LispMain LispMain.cpp


# for all clean and squeaky, go into each directory and make it
all clean squeaky TAGS:
	for each in ${DIRS}; do make -C $$each $@; done
