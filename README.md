ntuple
======

This package contains tools for working with EDM-style ntuples. A separate CMSSW setup is foreseen,
since the EDM-style ntuples need very few supporting libraries apart from the base CMSSW setup.

Contents
--------

* ``CMSSW/src/SingleTopPolarization/FWTools`` contains the wrappers for accessing the EDM objects from C++.
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
``git submodule add git@github.com:jpata/stpol_testcode1.git CMSSW/src/SingleTopPolarization/stpol_testcode1``
3. Compile your code using the standard CMSSW command ``scram b SingleTopPolarization/stpol_testcode1`` 

### Python
To create some code that uses the python library of ``$STPOL_DIR/src/headers/stpol.py``, considerably less setup is required.
One should simply follow the example of ``src/test.py`` code can be placed/run from anywhere. Versioning is up to the developer.

Troubleshooting
---------------

### Generic help

Please always check and report the version hash of the main code and all the submodules using

> git fetch origin; git log HEAD..origin/master --oneline; git rev-parse HEAD; git submodule status --recursive

If any of the submodule hashes contain a ***+*** in the beginning, you need to run

> git submodule update --recursive

### Errors related to `src/ntuples/src/test.py`
    
    Traceback (most recent call last):
      File "src/test.py", line 37, in <module>
        print "bjet_pt=", e.tchan.bjet.pt(event)
    AttributeError: 'Event' object has no attribute 'tchan'
    make: *** [testpy] Error 1

* Check that you have the latest version of `stpol/src/headers/stpol.py` by doing `git fetch origin; git log HEAD..origin/master --oneline`
* Make sure that you have correctly sourced `stpol/setenv.sh` and that `$STPOL_DIR` is pointing to where it should.
