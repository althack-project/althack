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

The most up to date documentation can be found `here <https://althack-game.readthedocs.io/en/latest/>`_.

.. image:: https://github.com/fairlight1337/althack/blob/45dfa213c379c123781dc645187bce6d9643c8bf/assets/20220901_althack_main_window.png
  :width: 600
  :alt: AltHack Main Window Screenshot

------------
How to Build
------------

To build the main application, run the following:

.. code-block:: bash

    git clone https://github.com/fairlight1337/althack
    mkdir build
    cd build
    cmake ..
    make

To build the documentation instead of the main application, change the `make` command to the following:

.. code-block:: bash

    make documentation

The documentation can be found under ``build/docs/sphinx`` and ``build/docs/doxygen``, respectively.

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
