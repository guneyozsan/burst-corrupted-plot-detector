# burst-corrupted-plot-detector
**Scans Burst mining logs and helps detecting corrupted plot files.**

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/develop/Screenshots/BurstCorruptedPlotDetector.png)

Scans Burst mining logs and helps detecting corrupted plot files so that problematic plot files can be re-plotted. It looks for deadlines conflicting with server and report related stats.

Currently only Blago Miner logs are supported.

Written in C++ to support PC, Mac and Linux. Tested only on Windows. Any testers are appreciated.

## Usage
Either pass the path of the directory of your mining log files as arguments or copy the executable into the directory that contain your mining logs and run it there (probably "Qbundle_1.6\BlagoMiner\Logs").

**Example:**

D:\Qbundle_1.6\BlagoMiner\Logs>BurstCorruptedPlotDetector.exe

or

AnyPath>BurstCorruptedPlotDetector.exe D:\Qbundle_1.6\BlagoMiner\Logs E:\Qbundle_1.5\BlagoMiner\Logs

Results are also saved to a file in the same directory with the executable.

## Release
This version is tested using a limited number of mining logs. Any feedback is appreciated.

Latest version can be downloaded from the [releases section](https://github.com/guneyozsan/burst-corrupted-plot-detector/releases).

For reporting bugs or feature requests please open an issue [here](https://github.com/guneyozsan/burst-corrupted-plot-detector/issues) 


## License
The project is open source and published under GNU General Public License. More details can be found in the LICENSE.md file, in the source files or at <http://www.gnu.org/licenses>.

The file dirent.h has a different licensing, which is MIT license. Please refer to the file for details.

## Links
* **About the author:**
http://www.guneyozsan.com
* **Contact:**
guney@guneyozsan.com
