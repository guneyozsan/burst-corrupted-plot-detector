# Burst Corrupted Plot Detector (Burst CPD)
**Scans Burst mining logs and helps detecting corrupted plot files.**

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/master/Screenshots/burst-corrupted-plot-detector-v1.0.0-x64.gif)

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/master/Screenshots/burst-corrupted-plot-detector-v1.0.0-x64.png)

Scans Burst mining logs and helps detecting corrupted plot files so that problematic plot files can be re-plotted. It looks for deadlines conflicting with server and report related stats.

Conflicts found does not necessarily mean that the plot file is corrupt. Consider re-plotting if a consistent pattern is noticeable and different from other plot files.

Currently only Blago Miner logs are supported.

Written in C++ to support PC, Mac and Linux. Tested only on Windows. Any testers are appreciated.

## Usage

`BurstCPD [<log_path>...]`

**Example:**

Copy to miner logs directory and run it:

`C:\MyBlagoMiner\Logs>BurstCPD`

or

Pass paths to miner logs as arguments and run from anywhere:

`...AnyPath>BurstCPD D:\MyBlagoMiner\Logs E:\MyOtherBlagoMiner\Logs`

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
