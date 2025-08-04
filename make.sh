ld -O3 -o output_program \
  /usr/lib/x86_64-linux-gnu/crt1.o \
  /usr/lib/x86_64-linux-gnu/crti.o \
  main.o \
  -L/usr/lib/x86_64-linux-gnu \
  -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lcurl -lc \
  /usr/lib/x86_64-linux-gnu/crtn.o \
  -dynamic-linker /lib64/ld-linux-x86-64.so.2