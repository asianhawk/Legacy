filename=`date '+%m%d%y'`
filename="/mnt/tucson/aik2_$filename.tgz"

#echo "$filename"

echo "`tar -czvf $filename *`"
