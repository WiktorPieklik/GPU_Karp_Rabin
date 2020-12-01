#!/usr/bin/env bash

if [ $# -eq 0 ]
then
        echo "Missing arguments!"
        echo "(run $0 -h for help)"
        echo ""
        exit 0
fi

dehumanise() {
    echo $1 | awk \
      'BEGIN{IGNORECASE = 1}
       function printpower(n,b,p) {printf "%u\n", n*b^p}
       /[0-9]$/{print $1;next};
       /K(iB)?$/{printpower($1,  2, 10)};
       /M(iB)?$/{printpower($1,  2, 20)};
       /G(iB)?$/{printpower($1,  2, 30)};
       /T(iB)?$/{printpower($1,  2, 40)};
       /KB$/{    printpower($1, 10,  3)};
       /MB$/{    printpower($1, 10,  6)};
       /GB$/{    printpower($1, 10,  9)};
       /TB$/{    printpower($1, 10, 12)}'
}

while getopts "h" OPTION; do
        case $OPTION in


                h)
			echo "Generates file of a given size populated with characters"
                        echo "Usage:"
			echo "$0 FILE_NAME SIZE [PATTERN]"
			echo "                 FILE_NAME - name of the output file"
			echo "                      SIZE - size in bytes; accepts human readable abbreviations i.e. 500K, 1M"
                        echo "                 [PATTERN] - text to fill the file"
                        echo ""
                        echo "$0 -h "
                        echo ""
			echo "Options:"
			echo "   -h     help (this output)"
                        exit 0
                        ;;

        esac
done

if [ $# -eq 2 ]
then
	< /dev/urandom tr -dc "\t\n [:alnum:]" | head -c$2 > $1
fi

if [ $# -eq 3 ]
then
	rm $1
	FILE_SIZE=$(dehumanise $2)
	PATTERN_SIZE=$(echo $3 | wc -c)
	WORDS=$((FILE_SIZE / PATTERN_SIZE))
	touch $1
	for ((i = 0 ; i < $WORDS ; i++)); do
  		echo -n $3>>$1
	done	
fi

