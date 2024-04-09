compile() {
	g++ -std=c++20 -Wall -Wfatal-errors -Wconversion -DLOC -fsanitize=address,undefined -g -o$1 $1.cpp
}
libhash() {
	cat $1.cpp | cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
}