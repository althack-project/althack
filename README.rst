=======
AltHack
=======

|build-status| |docs|

This file will contain useful information about the AltHack project.
Stay tuned!

`AltHack Project Website <https://althack-game.com>`_ (WIP)


.. |build-status| image:: https://circleci.com/gh/fairlight1337/althack.svg?style=svg
    :alt: build status
    :target: https://circleci.com/gh/fairlight1337/althack

.. |docs| image:: https://readthedocs.org/projects/althack-game/badge/?version=latest
    :alt: Documentation Status
    :scale: 100%
    :target: https://althack-game.readthedocs.io/en/latest/?badge=latest


------------
How to Build
------------

To build the main application, run the following:
```bash
git clone https://github.com/fairlight1337/althack
mkdir build
cd build
cmake ..
make
```

To build the documentation instead of the main application, change the `make` command to the following:
```bash
make documentation
```


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
