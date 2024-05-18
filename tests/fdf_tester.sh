#!/bin/bash

RED="\x1B[31m"
GRN="\x1B[1;32m"
YEL="\x1B[33m"
BLU="\x1B[34m"
MAG="\x1B[35m"
BMAG="\x1B[1;35m"
CYN="\x1B[36m"
BCYN="\x1B[1;36m"
WHT="\x1B[37m"
RESET="\x1B[0m"
LINEP="\033[55G" 
FAIL=false

usage() {
	cat <<EOF
Usage: $0 [options] [--] [file...]

Arguments:

  -f <val>, --file <val>, --file=<val>
	After setting this parameter, an argument must follow with relative 
	path to the directory where the norminette check should take place.
	e.g. [bash ./norminette_tester -d ./src]
	Without this paramater the program will not continue

  -h, --help
	Display this usage message and exit.

EOF
}

# handy logging and error handling functions
log() { printf '%s\n' "$*"; }
error() { log "ERROR: $*" >&2; }
fatal() { error "$*"; exit 1; }
usage_fatal() { error "$*"; usage >&2; exit 1; }

# parse options
while [ "$#" -gt 0 ]; do
	arg=$1
	case $1 in
		# convert "--opt=the value" to --opt "the value".
		# the quotes around the equals sign is to work around a
		# bug in emacs' syntax parsing
		--*'='*) 
		shift;
		set -- "${arg%%=*}" "${arg#*=}" "$@";
		continue;;
		-f|--file) 
		file=$2
		shift 2
		;;
		-h|--help)
		usage;
		exit 0
		;;
		--)
		shift;
		break
		;;
		-*)
		usage_fatal "unknown option:'$1'"
		;;
		*)
		break
		;; # reached the list of file names
	esac
done

# arguments are now the file names


if [ -n "$file" ];
then :
else 
usage_fatal "option '-f, --file' requires a value"
exit 1
fi

##### input tests

# valgrind ./fdf arg1 arg2 arg3 etc




##### testing maps 


# valgrind ./fdf test correct maps

# valgrind ./fdf test incorrect maps





# headers=$(find $dir -type f -name "*.h")

# files=$(find $dir -type f -name "*.c")

# if [ $print_intro = true ];
# then echo -e "${YEL}Norminette${RESET}" 
# else :
# fi

# for header in $headers
# do
# norminette $header >>norminette.log 2>&1
# status=$?
# if [ $status -eq 0 ];
# then echo -e "${BMAG}$header ${LINEP}${GRN}OK${RESET}" 
# else 
# echo -e "${BMAG}$header ${LINEP}${RED}FAIL${RESET}"
# FAIL=true
# fi
# done

# for file in $files
# do
# norminette $file >>norminette.log 2>&1
# status=$?
# if [ $status -eq 0 ];
# then echo -e "${BMAG}$file ${LINEP}${GRN}OK${RESET}" 
# else 
# echo -e "${BMAG}$file ${LINEP}${RED}FAIL${RESET}"
# FAIL=true
# fi
# done

# if [ $FAIL = true ];
# then echo -e "${RED}Check norminette_tester/norminette.log for errors${RESET}"
# fi
# exit 0