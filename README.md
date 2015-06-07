![R3E](https://cloud.githubusercontent.com/assets/12783101/8024034/cd3c7c84-0d24-11e5-9e5f-3bf6fbab713f.png)
# Shared Memory API

This is a small sample application showing how to use the shared memory API for 
[RaceRoom Racing Experience][r3e] (R3E).

The sample will poll for RRRE.exe for ten minutes, and if/when it finds the
application it will print some of the live data for another ten minutes.


## Prerequisites

- [RaceRoom Racing Experience][r3e]
- Any C89-compatible C/C++ compiler should be fine. There are project files for
Visual Studio 2010 and 2013 in the `build` directory. You can download the free
Community version of Visual Studio 2013 [here][vs2013].


## License

See [LICENSE](LICENSE).


[r3e]: http://game.raceroom.com/
[vs2013]: https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx