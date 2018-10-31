# EntropyIncreaser
A simple tool written in C that increases the entropy count of /dev/urandom. You have to run it as sudo.

WARNING! Increasing the entropy count without actually feeding entropy in the pool poses a security issue. This tool does **NOT** feed actual randomness into the pool, it will only tell the kernel to increase it's estimation. I only use it on virtual machines that don't have enough entropy after bootup to initialize the entropy pool of urandom and don't need good entropy. **USE AT YOUR OWN RISK!**
