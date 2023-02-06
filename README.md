
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

# run
use this command

    ./seabattle

# notice about network
1. for online gaming you must have ftp server. for this we recommend use your android device and install a ftp server app
on it. another notice if you don't want to use your android device as ftp server you must use a __linux__
device for ftp server.
2. after setup ftp server, you must change files ftp-download, ftp-upload, WINftp-download and WINftp-upload in ftpc folder as shown in these files.
3. before start the game, you must upload conf_online_data.bin (with name online_data.bin in ftp server) to your ftp server. for this, you must use below command.<br><br>
    
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
   
# Additional Information
This project is an academic(university) project in a two-person group with accounts
1. www.github.com/khodekhadem
2. www.github.com/aligrand


