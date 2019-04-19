Prerequisites: Allegro 5.2 installed in your system (5.2.4 recommended)

How to install the library:

1. Clone the GitHub repository with "git clone https://github.com/EnricRG/PID-UdG" and run "make" on the main directory. This will generate a file called libWindowAddon.so.
2. Take libWindowAddon.so and put it inside /usr/lib/ folder, or somewhere that the compiler can find it.
3. Put the headers somewhere the compiler can find them. The headers are inside the include folder. My recommendation is to put them into /usr/include.
4. Done. Go to test folder and run make command to check that all went right. Then run test executable and check if you see a black thin circle on a white screen.
5. Have fun.
