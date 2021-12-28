# woody-woodpacker
ELF/Mach-O Executable patcher. Injects arbitrary code and encrypts the base code then decrypts it at runtime.

Currently supports : ELF 64bits binaries

Work in progress : Mach-O (64bits) and ELF 32bits


# Run in docker
```
docker build -t woody .
./run.sh
docker exec -it woody bash 
cd woody; make
```
# Run locally
```
cd srcs
make
```
# Program usage
```
./woody_woodpacker exec_file [optional_encryption_key]
```
if no key is passed a random one will be generated
