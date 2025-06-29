# Wthr

## Dependencies
- **Linux** (Tested on Debian 12.5.0 and Gentoo)  
- **Compiler**: `g++` (GCC 8 or later required for C++20 support)  
- **Build tools**: `make`, `pkg-config`  
- **Libraries**: `libncurses-dev`

 For Debian based distros the dependencies can be resolved with:
 ```sh
sudo apt install build-essential pkg-config libncurses-dev
```

If you do not have access to a Linux install you can use https://distrosea.com.
You will need to create an account to be able to access the internet and install the necessary packages.
Once in the Debian 12.5.0 Standard emulator run these commands to get started:
```bash
sudo apt update
sudo apt install git build-essential pkg-config libncurses-dev
git clone https://github.com/SharkAce/wthr.git
cd wthr
make -j2
make run
```

## Building
```sh
make
```

## Running
```sh
make run
```
