rm -rf System.Runtime.Serialization.dll libsqlite3.0.dylib JSon2BJSon.zip JSon2BJSon

curl -L "https://docs.google.com/uc?export=download&id=0B7mEHYPXtU8iS0xIOFF3WkFRQ2c" > System.Runtime.Serialization.dll

curl -L "https://docs.google.com/uc?export=download&id=0B7mEHYPXtU8ieUY2dE0zTHN5QzA" > libsqlite3.0.dylib

curl -L "https://docs.google.com/uc?export=download&id=0B7mEHYPXtU8iN0pZTWNIZzJZRUU" > JSon2BJSon.zip
unzip JSon2BJSon.zip
cd ./JSon2BJSon
./build.sh
cd ../
rm -rf JSon2BJSon.zip JSon2BJSon
