


```
sudo apt update
sudo apt install -y build-essential gcc cmake
sudo apt install -y libglib2.0-dev liblzma-dev libxcb-image0 libxcb-keysyms1 libxcb-xfixes0 libxcb-xkb1 libxcb-shape0 libxcb-shm0 libxcb-randr0 libxcb-xtest0 libgbm1 libxtst6 libgl1
git clone https://github.com/linanw/zoom_v-sdk_linux_bot.git
cd zoom_v-sdk_linux_bot/
cmake -B build
cd build/
make
```

####
there is additional libraries needed for http post request
`curl.h` 

references
https://stackoverflow.com/questions/51317221/how-to-use-libcurl-in-c-to-send-a-post-request-and-receive-it
https://stackoverflow.com/questions/69861500/making-a-post-request-in-c-with-curlpp

To run this example, you need to have the curl headers installed

#Install header files and library for cURL
`sudo apt install libcurl4-openssl-dev`
#Download sample cpp file
curl -sLO https://gist.github.com/alghanmi/c5d7b761b2c9ab199157/raw/curl_example.cpp
#Compile and run the code
g++ curl_example.cpp -o curl_example -lcurl
./curl_example
The only caveat is that when dealing with SSL connections, they need to use the OpenSSL libraries.

//todo
stream to rtmp (currently not working, handled in onchatmessagereceived)
call localhost:8888
