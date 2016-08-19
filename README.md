# scan-report_probe
This is an openwrt package to scan in monitor mode probe over wifi channel with periodic report to a server through http post.


## file structure

Under the `src` folder the source files and scripts are organized in this way:
* scanReportProbe.conf
  * This is a configuration file for the tool. At installation time is installed in `/etc/scanReportProbe`
* data
  * In case the software need some additional files it's possible to put them in this folder. At installation time everithing in this folder is copied in `/usr/share/scanReportProbe`
* runScript
  * In this folder is positioned the `scanReportProbe` script that at installation time is copied in `/etc/init.d`. This script is a normal init script needed to obatain the autostart of the program at boot time.
* scan-report_probe
  * This folder is for the source files and the classical c makefile.

  
## installation

Copy the whole folder in `package/utils/` and from the main folder of openwrt run `make menuconfig`. 
After selecting the packet under the folder `utils` with the `M` exit from the utility saving the configuration.
At this point it's possible to build and compile the tool with `make package/scanReportProbe/compile` the ipk file is generated under the `bin` folder.