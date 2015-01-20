filename=`date '+%m%d%y'`
filename="/mnt/floppy/aik2_$filename.tgz"

#echo "$filename"

echo "`tar -czvf $filename *`"
