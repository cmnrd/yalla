#!/bin/bash

BASE_DIR="`pwd`"
DIRECTORY="doc"
echo "$DIRECTORY"
echo "$BASE_DIR"


# test for doc/html directory
if [ ! -d "$DIRECTORY" ];
then
	echo "Doc folder not found - fetching doc repo"
	mkdir doc
	cd doc
	git clone -b gh-pages git@github.com:chrism333/yalla.git
	mv yalla html
	cd $BASE_DIR
else
	echo " Doc folder found - updating repo first"
	 cd doc/html
	 git checkout gh-pages
	 git pull
	 cd $BASE_DIR
fi

echo "updating doxygen files"
doxygen yalla.doxyfile | grep "finished"
echo
cd doc/html
git add *
git commit -m "updated documentation"
git push origin gh-pages
cd $BASE_DIR
echo "all done"

