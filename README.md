# burst-corrupted-plot-detector
**Scans Burst mining logs and helps detecting corrupted plot files.**

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/develop/Screenshots/BurstCorruptedPlotDetector.png)

The tool scans Burst mining logs and helps detecting corrupted plot files so that problematic plot files can be re-plotted. It looks for deadlines conflicting with server and report related stats.

Currently only Blago Miner logs are supported.

Written in C++ to support PC, Mac and Linux. Tested only on Windows. Any testers are appreciated.

## Release
This is a pre-release version and only tested using a limited number of mining logs. Latest version can be downloaded from the [releases section](https://github.com/guneyozsan/burst-corrupted-plot-detector/releases).

## Usage
Copy the executable into the directory that contain your mining logs (probably "Qbundle_1.6\BlagoMiner\Logs"). Results will be saved to a file in the same directory with the executable.

Please run the executable without any arguments. Giving path as argument is supported but it doesn't work as intended. This will be fixed soon.

## License
The project is open source and published under GNU General Public License. More details can be found in the LICENSE.md file, in the source files or at <http://www.gnu.org/licenses>.

The file dirent.h has a different licensing, which is MIT license. Please refer to the file for details.

## Links
* **About the author:**
http://www.guneyozsan.com
* **Contact:**
guney@guneyozsan.com
