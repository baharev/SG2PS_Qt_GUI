
**Practically everything with the GUI is case sensitive.**
==========================================================


Shared source files
-------------------

The following files are shared by the back end and the GUI:
 
 - `ExitStatus.hpp`,
 - `ReservedColumnNames.hpp`, and
 - `ReservedColumnNames.cpp`.

If a new exception is thrown by the back end, the corresponding 
`Code` must be introduced in the `enum` of the `ExitStatus`. In the back
end, don't forget to catch the new exception in `main()`. In the GUI, 
the corresponding error message needs to be added.

When a new RGF file is created, the GUI writes all the allowed column 
names into the header. These names are hard-coded in the 
`ReservedColumnNames.cpp` file. If the back end introduces a new column
name, the corresponding `enum` must be updated (currently, it is 
`record_name` in `checkrgffilecontent.cpp`).
 
Please keep in mind that the copyright notice of the GUI is managed 
separately, and these shared files have that copyright on the top.


The GUI code base
=================

The source code was searched for string literals with the following 
regex `\"(\\.|[^"])*\"`.


ConvertAllEps
-------------

It assumes that the EPS files in the subfolders of 

 - `5_PS_SEPARATED`, and
 - `6_WELL_PS_SEPARATED` have to be converted.

No error is reported if any of these two folders does not exist. It is 
assumed that the EPS files have extension `.eps`, strictly lower case.

It is assumed that the `ps2pdf` convert generates pdf files with 
extension `.pdf`, and with the exact same name as its input EPS file 
was.


GUISettings
-----------

By default, the external programs SG2PS (back end) and the EPS to PDF 
converter are expected to be `sg2ps` and `ps2pdf`. 

On Windows, the command `sg2ps` can invoke, for example, `SG2PS.exe` 
(note that SG2PS is upper case in `SG2PS.exe`, and has an additional 
`.exe` extension too). This is Windows specific only, and won't work on 
Linux or Mac.


InfoWidget
----------

The back end is supposed to use the following extensions: 
`.rgf`, `.set`, `.xy`, `.trj`. Note that they must be lower case.

If a set of files in a directory have the same name but different 
extensions, then it is assumed that they belong to the same project. 
Note that this is again case sensitive. For example, if `abc.rgf` and 
`abc.set` are in the same directory, then they belong to the same 
project called `abc`. However, the file `Abc.xy` in the same directory
does *not* belong to the project `abc`; it belongs to the `Abc` project.


Launcher
--------

The following command line flags must be understood by the back end: 

 - `-v` and the back end is supposed to return a single line string like
   `24 Oct 2015, 19:41:24`,
 - `--version-id` and the back end is supposed to return a single line 
   string like `20151024194124`.

The back end **must not** print the banner when executed with these 
flags.

No flag is passed to the back end when executed with a project. (The 
flag `--gui` used to be passed previously.)


MainWindow
----------

The followings are hard-coded:

 - name of the manual: `manual.pdf`,
 - link to the homepage: http://www.sg2ps.eu/index.htm
 - name of the demo file: `demo.rgf`,
 - XY file header: `LOCATION    LOC_X    LOC_Y    FORMATION`,
 - TRJ file header: `DEPTH    LOC_X    LOC_Y`.

(The RGF file header is hard-coded in `ReservedColumnNames.cpp`.)


Option
------

See: https://github.com/baharev/SG2PS_Qt_GUI/blob/master/Option.cpp

The GUI is supposed to know *all* documented settings for the back end.
Since it is easy to make typos or to miss a new setting, the back end is
supposed to throw a `set_error` if the settings file is incorrect. This 
way, the typos will hopefully be found during development.


Runner
------

A new log file is created whenever the back end is run, **any existing 
`log.txt` in the directory of the input files will be 
overwritten.** The log file is called `log.txt`; this name is 
hard-coded. Similarly, **any existing settings file of the back end will
be overwritten** if it has the same name as the project.

The back end is supposed to create a new text file called 
`project_folder_name` (or overwrite it if it exists) in the directory of
the input files and with a single line content, giving the generated 
project folder name (like `20151024-191518_DEMO`). This is necessary for
the EPS to PDF conversions: The GUI must find the newly created output 
folder. Once the back end finishes, and the GUI collects the name of the 
newly generated project folder name, **the file `project_folder_name`
is deleted.**

In short, three files are overwritten or deleted in the folder of the 
input files:

 - `log.txt`,
 - `<project name>.set`, and
 - `project_folder_name`.

The Demo assumes the existence of a `demo.rgf` file. The GUI Settings 
are ignored when a project called `demo` is run, and the result 
directory is shown anyway, together with the following two result PDF 
files:

 - `5_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE.pdf`, and
 - `6_WELL_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE_TILTED.pdf`.


SettingsWidget
--------------

In the settings file of the back end, it is assumed that the lines look 
like: `key:\tvalue`, that is, the key and the value are separated by 
`":\t"`. The back end assumes no new line at the end of the last line.



Known issues
============

The `Advanced` > `GUI Settings` is currently broken: The external 
programs are apparently not found when given with the full path. 
(Reason: `ShellExecute`?) This part of the code, responsible for 
executing external programs, must be cleaned up both on Windows and on 
Linux.

Apparently, it is mostly fixed for spreadsheets, grep for FIXME.
