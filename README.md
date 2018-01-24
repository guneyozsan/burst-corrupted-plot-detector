# burst-corrupted-plot-detector
**Scans Burst mining logs and helps detecting corrupted plot files.**

![Burst corrupted plot detector screenshot](https://github.com/guneyozsan/burst-corrupted-plot-detector/blob/develop/Screenshots/BurstCorruptedPlotDetector.png)

The tool scans mining logs and help detecting corrupted plot files so that you can re-plot the problem files. It looks for deadlines conflicting with server and report related stats.

Currently only Blago Miner logs are supported.

Written in C++ to support PC, Mac and Linux. Tested only on Windows. Any testers are appreciated.

## Release
This is a pre-release version. It doesn't give consistent results if deadlines are very frequent, especially more than one each block. Otherwise it is mostly useful.

You need to place the executable in the same directory with logs. Passing the path with arguments is supported but it doesn't work internally yet.

## License
The project is open source and published under GNU General Public License. More details can be found in the LICENSE.md file, in the source files or at <http://www.gnu.org/licenses>.

## Links
* **About the author:**
http://www.guneyozsan.com
* **Contact:**
guney@guneyozsan.com
