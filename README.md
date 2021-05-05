# qml-forward-gallery
Simple slideshow gallery application written in Qt/Qml. (originally based on qbijin-tokei application)

Originally based on [qbijin-tokei](https://github.com/dev-0x7C6/qbijin-tokei)

![](https://devwork.space/wp-content/uploads/2021/05/qml-forward-gallery.png)

#### Command line usage
```
Usage: ./qml-forward-gallery [options]

Options:
  -h, --help                     Displays help on commandline options.
  --help-all                     Displays help including Qt specific options.
  -v, --version                  Displays version information.
  -d, --directory <directories>  open directory.
```

#### Installation process
```console
user@host # git clone https://github.com/dev-0x7C6/qml-forward-gallery.git
user@host # cd qml-forward-gallery
user@host # cmake . -DCMAKE_INSTALL_PREFIX=/usr
user@host # make -j$(nproc)
root@host # make install
```
