# fidel-musicplayer
An intuitive, feature rich musicplayer built around the linux platform

   * [fidel-musicplayer](#fidel-musicplayer)
      * [Screenshots](#screenshots)
         * [Powerful Overview search](#powerful-overview-search)
      * [Compile](#compile)
      * [Notes](#notes)


## Screenshots

[![Library View](https://github.com/kloke-source/fidel-musicplayer/blob/master/Screenshots/fidel-library-view.png)](#Screenshots)

[![Spectrum View](https://github.com/kloke-source/fidel-musicplayer/blob/master/Screenshots/fidel-spectrum-visualizer.png)](#Screenshots)

### Powerful Overview search

[![Popover Search View](https://github.com/kloke-source/fidel-musicplayer/blob/master/Screenshots/fidel-popover-search-3.png)](#Screenshots)

## Compile

To compile fidel, clone the repository and enter the build directory, then follow the compile steps below.

```bash
git clone https://github.com/kloke-source/fidel-musicplayer
cd fidel-musicplayer/build
./compile
make
```

To run fidel without installing go back to the root project folder and run the fidel binary 

```
./fidel
```

To install, run `sudo make install` from within the build directory

## Notes

Fidel musicplayer is still very experimental and new features are on the way. The project's GUI is also currently in the progress of being moved to Qt from Gtkmm.
