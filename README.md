ntuple
======

This package contains tools for working with EDM-style ntuples. A separate CMSSW setup is foreseen,
since the EDM-style ntuples need very few supporting libraries apart from the base CMSSW setup.

Setting up the code
-------------------

Clone the repo into the the ``$STPOL_DIR/src`` directory. This is needed to access the singletop polarization specific headers from ``$STPOL_DIR/src/headers``.

1. Run ``./setup.sh`` to set up CMSSW and get the example code as a submodule.
2. Run ``make`` to compile and test the simple example ``stpol_testcode1`` of the C++ interface and ``src/test.py`` of the python interface.

Using this library
-----------------

The implementation of this library is decoupled from any code that uses it via git submodules.
The advantage is that development workflow of a submodule X is not affected by the workflow of the main module or other submodules.

To create your own code using this module (C++)

1. Create a new repo using the example of https://github.com/jpata/stpol_testcode1
2. Add your newly created repo to the ``ntuple`` package as a submodule by doing
``git submodule add git@github.com:jpata/stpol_testcode1.git CMSSW/src/SingleTopPolarization/stpol_testcode1``
3. Compile your code using the standard CMSSW command ``scram b SingleTopPolarization/stpol_testcode1`` 

To create some code that uses the python library of $STPOL_DIR/src/headers/stpol.py, considerably less setup is required.
One should simply follow the example of ``src/test.py`` and the resulting file can be placed/run from anywhere. Versioning is up to the developer.
