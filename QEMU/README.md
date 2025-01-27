# To run two clients using QEMU
- qemu-ifup
```
#!/bin/sh
ifconfig $1 0.0.0.0 up
brctl addif br0 $1
```
- to setup bridge network 
```
sudo ip link add br0 type bridge
sudo ip link set br0 up

sudo apt update
sudo apt install bridge-utils dnsmasq

# Create bridge
sudo ip link add br0 type bridge
sudo ip addr add 192.168.0.1/24 dev br0
sudo ip link set br0 up

# Enable IP forwarding
sudo sysctl -w net.ipv4.ip_forward=1

sudo mkdir -p /srv/tftp
sudo chmod -R 777 /srv/tftp

#First instance:
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot \
-sd sd1.img \
-net tap,ifname=tap0,script=./qemu-ifup -net nic

#Second instance:
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot \
-sd sd2.img \
-net tap,ifname=tap1,script=./qemu-ifup -net nic

setenv ipaddr 192.168.0.2   # For first instance (change for second)
setenv serverip 192.168.0.1 # Host machine (TFTP server)
setenv gatewayip 192.168.0.1
setenv netmask 255.255.255.0
saveenv
```
- built ur RFS
- add client_qemu to RFS in both
- setup network 
```
#in each QEMU instance
ip addr add 192.168.0.2/24 dev eth0 # First VM
ip addr add 192.168.0.3/24 dev eth0 # Second VM
ip link set eth0 up
```
- run server first on Raspberry_Pi or PC 
- then run client_qemu on both instance
    
    
