# Burst Corrupted Plot Detector (BurstCPD)
**Scans Burst mining logs and helps detecting corrupted plot files.**

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/master/Screenshots/burst-corrupted-plot-detector-v1.0.0-x64.gif)

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/master/Screenshots/burst-corrupted-plot-detector-v1.1.0-x64.png)

Scans Burst mining logs and helps detecting corrupted plot files so that problematic plot files can be re-plotted. It looks for deadlines conflicting with server and report related stats.

* Please note that this tool scans logs, not plot files, which means the plot file should be in use for a while to give meaningful results.

* Conflicts found does not necessarily mean that the plot file is corrupt. Consider re-plotting only if a consistent pattern that is different from other plot files is noticeable.

* Currently only Blago Miner logs are supported.

* Written in C++ to support PC, Mac and Linux.
* Tested only on Windows. Any testers are appreciated.

## Usage

Download and unzip the executable from the [releases section](https://github.com/guneyozsan/burst-corrupted-plot-detector/releases/latest): `Burst-Corrupted-Plot-Detector-v...-win-x64.zip`

### Option 1:

* Place the exe to the miner logs folder: `...BlagoMiner\Logs\`.
* Run it there by double clicking on it.
  * Alternatively you can run it from the command line: `...BlagoMiner\Logs>BurstCPD`

### Option 2:

Run the executable from the command line and pass the log path as an argument (supports multiple paths as arguments).

`BurstCPD [<log_path>...]`

**Example:**

`...AnyPath>BurstCPD D:\MyBlagoMiner\Logs E:\MyOtherBlagoMiner\Logs`

Analysis results will also be saved to a file near the executable.

## Compilation

### Windows:

* Download the source from [releases section](https://github.com/guneyozsan/burst-corrupted-plot-detector/releases/latest).
  * Or clone the repository using [git](https://git-scm.com/download/win): `git clone https://github.com/guneyozsan/burst-corrupted-plot-detector`
* Install [Visual Studio 2017](https://www.visualstudio.com/downloads/) (free Community version works).
* Open the project in Visual Studio.
* Switch the mode from `Debug` to `Release` (The option is on the toolbar).
* Build the project from the top menu: `Build/Build BurstCPD`
* Executable will be at `...\BurstCorruptedPlotDetector\x64\Release\`

## Issues and Feedback
This version is tested using a limited number of mining logs. Any feedback is appreciated.

For reporting bugs or feature requests please open an issue on [issues section](https://github.com/guneyozsan/burst-corrupted-plot-detector/issues) 

## License
The project is open source and published under GNU General Public License. More details can be found in the LICENSE.md file, in the source files or at <http://www.gnu.org/licenses>.

The file dirent.h has a different licensing, which is MIT license. Please refer to the file for details.

## Links
* **About the author:**
http://www.guneyozsan.com
* **Contact:**
guney@guneyozsan.com
