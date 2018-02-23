#!/bin/bash

cd /tmp/test/
ls *.tar.gz > ls.log	// 截断
ls *.tgz >> ls.log		// 追加

for i in $( cat ls.log  )
	do
		tar -zvf $i & > /dev/null
	done
rm -rf ls.log
