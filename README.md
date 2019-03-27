

```shell
cd /tmp

# Install spawn-fcgi
wget http://archive.ubuntu.com/ubuntu/pool/universe/s/spawn-fcgi/spawn-fcgi_1.6.4-2_amd64.deb
sudo dpkg -i /tmp/spawn-fcgi_1.6.4-2_amd64.deb

# Install libfcgi
wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/libfcgi/2.4.0-10/libfcgi_2.4.0.orig.tar.gz
tar -xf libfcgi_2.4.0.orig.tar.gz
cd libfcgi-2.4.0.orig
./configure 'CFLAGS=-O3 -s'
make 
sudo make install

mkdir -pv /var/app/bots6
cd /var/app/bots6
git clone https://github.com/TeaInside/tea-inside-bot-s6 .
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed ..
make
make install
```