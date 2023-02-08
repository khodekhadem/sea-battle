
[![Available_in](https://img.shields.io/badge/-Available%20in-555)]()
[![Windows](https://img.shields.io/badge/-WINDOWS-blue)](https://www.microsoft.com/en-us/windows)
[![Linux](https://img.shields.io/badge/-LINUX-blue)]()



[![Requirements](https://img.shields.io/badge/Requirements-gcc%20%2F%20git-blue)]()



# sea-battle
simple classic sea-battle with c in command line environment

# Requirements
* GCC (Mingw)
* git

# installation
first, clone the repository

    git clone https://github.com/khodekhadem/sea-battle

then, move to the directory

    cd sea-battle

compile the sources

    gcc -Wall sb_globdef.h s* -o seabattle
    gcc
# run
use this command

    ./seabattle

# notice about online gaming
1.for online gaming you need to config your  linux server with ansible , change ansible/hosts with your server ip and use this command to copy file to /etc/ansible/hosts

    cd ansible

    cp hosts /etc/ansible/hosts

now you can run my ansible playbook with this command
   
    ansible-playbook ftp.yml

your server will be configed automatically 

2.after setting up your server, you have to edit  ftp-download, ftp-upload, WINftp-download.txt and WINftp-upload.txt in ftpc directory.

3.before start the game, you have to upload conf_online_data.bin (in name of online_data.bin in ftp server) to your ftp server. for this, you must use below commands.<br><br>
    
   ```
  WINDOWS:
   
  > ftp <ip> <port>
  > <username>
  > <password>
  > put .\conf_online_data.bin ./online_data.bin
  ```
  ```
  LINUX:
   
  $ ftp <ip> <port>
  $ <username>
  $ <password>
  $ put ./conf_online_data.bin ./online_data.bin
  ```
4.if you use linux , run this command in temrinal

    ls -ltrh /bin | grep pftp
if you dont have any output you should edit seabattle_ftp.c and change
   
    pftp

with

    ftp -p
# Additional Information
This project is an academic(university) project in a two-person group with accounts
1. www.github.com/khodekhadem
2. www.github.com/aligrand


