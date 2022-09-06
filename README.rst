=======
AltHack
=======

|build-status| |docs|

This file will contain useful information about the AltHack project.
Stay tuned!

`AltHack Project Website <https://althack-game.com>`_ (WIP)


.. |build-status| image:: https://circleci.com/gh/althack-project/althack.svg?style=svg
    :alt: build status
    :target: https://circleci.com/gh/althack-project/althack

.. |docs| image:: https://readthedocs.org/projects/althack-game/badge/?version=latest
    :alt: Documentation Status
    :scale: 100%
    :target: https://althack-game.readthedocs.io/en/latest/?badge=latest

The most up to date documentation can be found `here <https://althack-game.readthedocs.io/en/latest/>`_.

.. image:: https://github.com/althack-project/althack/raw/main/assets/20220901_althack_main_window.png
  :width: 600
  :alt: AltHack Main Window Screenshot

------------
How to Build
------------

To build the main application, run the following:

.. code-block:: bash

    git clone https://github.com/althack-project/althack
    mkdir build
    cd build
    cmake ..
    make

To build the documentation instead of the main application, change the `make` command to the following:

.. code-block:: bash

    make documentation

The documentation can be found under ``build/docs/sphinx`` and ``build/docs/doxygen``, respectively.

-----------------------------
Cross Compilation for Windows
-----------------------------

The project can be built for Windows platforms. To cross-compile from a Linux host to a Windows target, run the following:

.. code-block:: bash

    git clone https://github.com/althack-project/althack
    mkdir build
    cd build
    cmake -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++ -DCMAKE_FIND_ROOT_PATH=/usr/i686-w64-mingw32 -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DWIN32=True ..
    make

----------
How to Run
----------

To run the main application file, run

.. code-block:: bash

    ./build/bin/althack-bin

after building the main application. The main binary supports various command line options, which can be displayed via

.. code-block:: bash

    ./build/bin/althack-bin --help

-------------------
Development Roadmap
-------------------

This section will be revised into time segments, release cadence, etc., but for the time being I'm
just collecting next steps and later make sense of their exact order and timing.

* Backend selection - When game starts, allow selection of server or client mode. Overridable
  through command line parameters.

* Account management in backend - At least in the server backend, accounts should be stored
  permanently and served to connecting clients.

* More to come
