UnattainiumV2 2.9.0
=====================

Copyright (c) 2009-2014 UnattainiumV2 Developers


Setup
---------------------
[UnattainiumV2 Core](http://bitcoin.org/en/download) is the original UnattainiumV2 client and it builds the backbone of the network. However, it downloads and stores the entire history of UnattainiumV2 transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once. If you would like the process to go faster you can [download the blockchain directly](https://bitcointalk.org/index.php?topic=145386.0).

Running
---------------------
The following are some helpful notes on how to run UnattainiumV2 on your native platform. 

### Unix

You need the Qt4 run-time libraries to run UnattainiumV2-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/unattainiumv2-qt (GUI, 32-bit) or bin/32/unattainiumv2d (headless, 32-bit)
- bin/64/unattainiumv2-qt (GUI, 64-bit) or bin/64/unattainiumv2d (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run unattainiumv2-qt.exe.

### OSX

Drag UnattainiumV2-Qt to your applications folder, and then run UnattainiumV2-Qt.

### Need Help?

* See the documentation at the [UnattainiumV2 Wiki](https://en.bitcoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#unattainiumv2](http://webchat.freenode.net?channels=unattainiumv2) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=unattainiumv2).
* Ask for help on the [UnattainiumV2Talk](https://bitcointalk.org/) forums, in the [Technical Support board](https://bitcointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build UnattainiumV2 on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-msw.md)

Development
---------------------
The UnattainiumV2 repo's [root README](https://github.com/bitcoin/bitcoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Coding Guidelines](coding.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on the [UnattainiumV2Talk](https://bitcointalk.org/) forums, in the [Development & Technical Discussion board](https://bitcointalk.org/index.php?board=6.0).
* Discuss on [#unattainiumv2-dev](http://webchat.freenode.net/?channels=unattainiumv2) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=unattainiumv2-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
