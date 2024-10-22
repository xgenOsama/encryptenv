```
a file with .env should be exists in the root dir to grap the keys and values from it
not .env file shouldn't contain any empty values 
gcc -o encryptenv.so encryptenv.c
./encryptenv.so
gcc -shared -o env.so -fPIC env.c
```