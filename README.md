# RIOT_Projects
## setup 
* setup RIOT-HOME (toolchain etc.) See getting started [here](https://doc.riot-os.org/getting-started.html)
* clone project with submodules (relic):
  
  ```
  git clone --recurse-submodules https://github.com/maksim-ka/RIOT_Projects
  cd RIOT_Projects
  ```
  * for getting latest commits of submodules
  ```
  git submodule update --remote --merge
  ```
* move into a project folder, e.g.: 
  ```
  cd relic_bench-native
  ```

* In the project folder run the following commands:
  *  `make` to compile
  *  `make flash term` to run (_`term`_ is for the output)
