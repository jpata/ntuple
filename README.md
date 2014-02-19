ntuple
======

This package contains tools for working with EDM-style ntuples. A separate CMSSW setup is foreseen,
since the EDM-style ntuples need very few supporting libraries apart from the base CMSSW setup.

Contents
--------

* ``CMSSW/src/FWTools/FWTools`` contains the wrappers for accessing the EDM objects from C++.
* ``Makefile`` is the main Makefile, supporting ``make setup/all/test``.

Setting up the code
-------------------

Clone the repo into the the ``$STPOL_DIR/src`` directory. This is needed to access the singletop polarization specific headers from ``$STPOL_DIR/src/headers``.

1. Run ``./setup.sh`` to set up CMSSW.

Using this library
-----------------

The implementation of this library is decoupled from any code that uses it via git submodules.
The advantage is that development workflow of a submodule X is not affected by the workflow of the main module or other submodules.

### Cpp
To create your own code using this module in C++

1. Create a new repo using the example of https://github.com/jpata/stpol_testcode1
2. Add your newly created repo to the ``ntuple`` package as a submodule by doing
``git submodule add git@github.com:jpata/stpol_testcode1.git CMSSW/src/FWTools/stpol_testcode1``
3. Compile your code using the standard CMSSW command ``scram b FWTools/stpol_testcode1`` 

Troubleshooting
---------------

### Generic help

Please always check and report the version hash of the main code and all the submodules using

> git fetch origin; git log HEAD..origin/master --oneline; git rev-parse HEAD; git submodule status --recursive

If any of the submodule hashes contain a ***+*** in the beginning, you need to run

> git submodule update --recursive
