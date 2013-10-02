ntuple
======

This package contains tools for working with EDM-style ntuples. A separate CMSSW setup is foreseen,
since the EDM-style ntuples need very few supporting libraries apart from the base CMSSW setup.

Setting up the code
-------------------

Clone the repo into the the ``$STPOL_DIR/src`` directory. This is needed to access the singletop polarization specific headers from ``$STPOL_DIR/src/headers``.

1. Run ``./setup.sh`` to set up CMSSW.
2. Run ``make`` to compile and test the simple example ``stpol_testcode1``.
3. 

Using this library
-----------------

The implementation of this library is decoupled from any code that uses it via git submodules.
The advantage is that development workflow of a submodule X is not affected by the workflow of the main module or other submodules.

To create your own code using this module

1. Create a new repo using the example of https://github.com/jpata/stpol_testcode1
2. Add your newly created repo to the ``ntuple`` package as a submodule by doing
``git submodule add git@github.com:jpata/stpol_testcode1.git CMSSW/src/SingleTopPolarization``
3. Compile your code using the standard CMSSW command ``scram b SingleTopPolarization/stpol_testcode1`` 
