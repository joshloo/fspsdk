===============
   FSP SDK
===============

FSP SDK is a fork of EDK2_ project. The purpose of this repo is to create a
basic infrastructure to support create FSP binary.  For demonstration, QEMU virtual
platform is used here.


QEMU FSP SDK Build Steps
------------------------
* Prepare EDK2 build environment following instructions listed `here <http://https://github.com/tianocore/tianocore.github.io/wiki/Getting-Started-with-EDK-II>`_

* Build QEMU FSP binary

.. code-block:: bash

  git clone https://github.com/joshloo/fspsdk.git
  cd fspsdk
  git submodule update --init
  # Build 32 bit QEMU FSP
  python buildFsp.py build -p qemu -a ia32
  
  64 bit build is not supported yet.

.. _EDK2: https://github.com/tianocore/edk2.git
