ntuple
======

This package contains tools for working with EDM-style ntuples. A separate CMSSW setup is foreseen, since the EDM-style ntuples need very little supporting libraries.

Setting up the code
-------------------

Clone the repo into the the ``$STPOL_DIR/src`` directory. This is needed to access the singletop polarization specific headers from ``$STPOL_DIR/src/headers``.

1. Run ``./setup.sh`` to set up CMSSW.
2. Run ``make`` to compile and test the simple example ``eventloop_example``.
