Steps for setting up doxygen
Run the following commands in commandline
->  git clone https://github.com/doxygen/doxygen.git
->  cd doxygen
->  mkdir build
->  cd build
->  sudo apt-get install flex
->  sudo apt-get install bison
->  cmake -G "Unix Makefiles" ..
 Note :  if you dont have cmake installed , get it by running the following command 
         -> > sudo apt-get -y install cmake
-> make
-> sudo make install
-> doxygen -g dconfig 

now go to directory where  your project is lying and run the following command there
-> doxygen -g dconfig 
now open the dconfig file and copy the sample config file given in this repository
change the following data

PROJECT_NAME = "what ever you want"

save and run the following command in terminal

-> doxygen dconfig

html folder will be generated , go inside it and open index.html in web browser.