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
LINEP="\033[75G" 
FAIL=false
LOG_DIR=logs/
FDF_LOG=fdf.log
FDF_MLOG=fdf_memory.log
FDF_MAP=fdf_map.log

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

mkdir -p logs

truncate -s 0 $LOG_DIR/$FDF_LOG
truncate -s 0 $LOG_DIR/$FDF_MLOG
truncate -s 0 $LOG_DIR/$FDF_MAP 

fail_unittest () {
printf "${BMAG} $file $1${RESET}"

coproc { timeout --preserve-status 1s sh -c " ./$file $1 >> $LOG_DIR/$FDF_LOG 2>&1"; }
COPROC_PID_backup=$COPROC_PID
wait $COPROC_PID_backup
status=$?

coproc { timeout --preserve-status 1s sh -c "valgrind --error-exitcode=42 --leak-check=full ./$file $1 >> $LOG_DIR/$FDF_MLOG 2>&1"; }
COPROC_PID_backup=$COPROC_PID
wait $COPROC_PID_backup
mstatus=$?

if [ $status == 0 ] || [ $status == 143 ];
then 
printf "${BMAG} ${LINEP}${RED}FAIL ${RESET}";
echo -e "Test: $file $1: expected status = 1; received status $status" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
if [ $mstatus == 42 ];
then 
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $1: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else 
if [ $mstatus == 143 ];
then
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $1: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else
printf "${GRN}MOK${RESET}\n";
fi
fi
else
printf "${BMAG} ${LINEP}${GRN}OK ${RESET}";
if [ $mstatus == 42 ];
then 
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $1: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else 
if [ $mstatus == 143 ];
then
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $1: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else
printf "${GRN}MOK${RESET}\n";
fi
fi
FAIL=true;
fi
}


##### input tests

echo -e "${BLU}----------------------------------
|            input tests          |
----------------------------------${RESET}" 

ARGS=$(find ../resources/incorrect_maps -type f)

for ARG in $ARGS
do
fail_unittest "$ARG"
done

##### testing maps 
#https://stackoverflow.com/questions/20017805/bash-capture-output-of-command-run-in-background
#https://stackoverflow.com/questions/9954794/execute-a-shell-function-with-timeout
#https://stackoverflow.com/questions/57877451/retrieving-output-and-exit-code-of-a-coprocess

echo -e "${BLU}----------------------------------
|            Map tests            |
----------------------------------${RESET}" 

invalids=$(find ../resources/incorrect_maps -type f)

for invalid in $invalids
do

ARG=$invalid

printf "${BMAG} $file $ARG${RESET}"

coproc { timeout --preserve-status 1s sh -c " ./$file $ARG >> $LOG_DIR/$FDF_LOG 2>&1"; }
COPROC_PID_backup=$COPROC_PID
wait $COPROC_PID_backup
status=$?

coproc { timeout --preserve-status 1s sh -c "valgrind --error-exitcode=42 --leak-check=full ./$file $ARG >> $LOG_DIR/$FDF_MLOG 2>&1"; }
COPROC_PID_backup=$COPROC_PID
wait $COPROC_PID_backup
mstatus=$?

if [ $status == 0 ] || [ $status == 143 ];
then 
printf "${BMAG} ${LINEP}${RED}FAIL ${RESET}";
echo -e "Test: $file $ARG: expected status = 1; received status $status" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
if [ $mstatus == 42 ];
then 
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $ARG: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else 
if [ $mstatus == 143 ];
then
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $ARG: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else
printf "${GRN}MOK${RESET}\n";
fi
fi
else
printf "${BMAG} ${LINEP}${GRN}OK ${RESET}";
if [ $mstatus == 42 ];
then 
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $ARG: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else 
if [ $mstatus == 143 ];
then
printf "${RED}MKO${RESET}\n";
echo -e "Test: $file $ARG: expected memory_status = 1; received memory_status $mstatus" >> $LOG_DIR/$FDF_MAP 
FAIL=true;
else
printf "${GRN}MOK${RESET}\n";
fi
fi
FAIL=true;
fi

done


if [ $FAIL = true ];
then echo -e "${RED}Check logs/*.log for errors${RESET}"
fi
exit 0